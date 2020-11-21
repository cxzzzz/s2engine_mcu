
#include  "dma.h"



const char* GET_DMA_NAME(DMA_ID id){
	switch(id){
		case FMDMA:return "FMDMA";
		case WMDMA:return "WMDMA";
		case BFDMA:return "BFDMA";
		case BMDMA:return "BMDMA";
		case WBDMA:return "WBDMA";
		case IFDMA:return "IFDMA";
		case OFDMA:return "OFDMA";
		default:
			assert(false);
	}
	return 0;
}

struct _DMA_INFO DMA_INFO;

volatile DMA_CTRL* FMDMA_CTRL = (DMA_CTRL*)FMDMA;
volatile DMA_CTRL* WMDMA_CTRL = (DMA_CTRL*)WMDMA;
volatile DMA_CTRL* BFDMA_CTRL = (DMA_CTRL*)BFDMA;
volatile DMA_CTRL* BMDMA_CTRL = (DMA_CTRL*)BMDMA;
volatile DMA_CTRL* WBDMA_CTRL = (DMA_CTRL*)WBDMA;
volatile DMA_CTRL* IFDMA_CTRL = (DMA_CTRL*)IFDMA;
volatile DMA_CTRL* OFDMA_CTRL = (DMA_CTRL*)OFDMA;

#define DMA_CTRL_REG( x )  ((volatile DMA_CTRL*)(x))

#define bits_assign(high,low,value)  ( value<<(low) )

void dma_config(DMA_ID dma, uint32_t timer,uint8_t sg_num,uint8_t fm_end){
	volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );
	uint32_t v = 0;
	if(timer != 0){
		v = v | bits_assign(7,7,1);

		dma_ctrl->CTRL.CONFIG_TIMER = timer; 
		//*( ((uint32_t*)dma) + 0x2) = timer;
	}
	v = v | bits_assign( 5,0 , sg_num );
	
	if( fm_end != 0)
		v = v | bits_assign( 6,6,1);
	
	//*( ((uint32_t*)dma) + 0x1 ) =  v;
	dma_ctrl->CTRL.CONFIG_TE_SG_FMEND = v;
}


void dma_reset(DMA_ID dma){
	//*(((uint32_t*)dma)+ 0x3) = 1;
	volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );
	dma_ctrl->CTRL.RESET = 1;

	//降低dma权重
	dma_weight_set(dma,0);
}

int dma_wait(DMA_ID dma){
		volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );
		
		
		uint32_t status;
		int error = 0;
		int end = 0;
	
		do{ 
			status = dma_ctrl->INFO.INFO_0;
			


			if( BIT(status,5) ){
				dbg_puts_d( "dma time out:\tid:%s",GET_DMA_NAME(dma));
				error = -3;
				end = 1;
			}
			if( BIT(status,4)|| BIT(status,3) ) 
			{
				dbg_puts_d( "dma write error:\tid:%s",GET_DMA_NAME(dma));
				error = -2;
				end = 1;
			}
			if( BIT(status,2)|| BIT(status,1) ) 
			{
				dbg_puts_d( "dma read error:\tid:%s",GET_DMA_NAME(dma));
				error = -1;
				end = 1;
			}
			if( BIT(status,0) )
			{
				//dbg_puts_d( "dma stopped:\tid%s",GET_DMA_NAME(dma));
				error = 0;
				end = 1;
			}
			if( error )
				dbg_puts_d("dma %s info0:%x", GET_DMA_NAME(dma),status);
			
			if(end) 
					return error;
			
		}while( 1 );
		
}

inline void dma_sg_set(DMA_ID dma,uint8_t sg_idx,uint32_t rd_addr,uint32_t wr_addr,uint32_t len){
	/*uint32_t* dma_addr = ((uint32_t*)(dma)) + (0x8 * 4) + (sg_idx * 3);
	*(dma_addr + 0) = rd_addr;
	*(dma_addr + 1) = wr_addr;
	*(dma_addr + 2) = len;
	*/
	volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );

	/*dbg_puts_d("%x set: %x", &(dma_ctrl -> CONFIG_DMA[sg_idx].RD_ADDR), rd_addr);
	dbg_puts_d("%x set: %x", &(dma_ctrl -> CONFIG_DMA[sg_idx].WR_ADDR), wr_addr);
	dbg_puts_d("%x set: %x", &(dma_ctrl -> CONFIG_DMA[sg_idx].LEN),len);
	*/
	assert( len%16 == 0);
	dma_ctrl -> CONFIG_DMA[sg_idx].RD_ADDR = rd_addr;
	dma_ctrl -> CONFIG_DMA[sg_idx].WR_ADDR = wr_addr;
	//dma_ctrl -> CONFIG_DMA[sg_idx].LEN = (len/16) - 1;
	dma_ctrl -> CONFIG_DMA[sg_idx].LEN =  len - 1;
}



int dma_int_clear(DMA_ID dma){
	//读取info0 时会清除dma中断
	volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );

	uint32_t info = dma_ctrl->INFO.INFO_0; 
	//uint32_t info = *( ((uint32_t*)dma) + 0x0 );
	return info;
}
	
inline void dma_enable(DMA_ID dma){
	
	//这里临时设置一个权重
	dma_weight_set(dma,128);
	//*( ((uint32_t*) dma) + 0 )  = 1;
	volatile DMA_CTRL* dma_ctrl = DMA_CTRL_REG( dma );
	dma_ctrl -> CTRL.CONFIG_START = 1;

}

void dma_weight_set(DMA_ID dma,int weight){
	switch( dma){
		case IFDMA:
			SDRAM_CTRL->WEIGHT_IFIFO = weight;
			break;
		case OFDMA:
			SDRAM_CTRL->WEIGHT_OFIFO = weight;
			break;
		case FMDMA:
			SDRAM_CTRL->WEIGHT_FM = weight;
			break;
		case BFDMA:
			SDRAM_CTRL->WEIGHT_BF = weight;
			break;
		case BMDMA:
			SDRAM_CTRL->WEIGHT_BM = weight;
			break;
		case WBDMA:
			SDRAM_CTRL->WEIGHT_SDRAM = weight;
			break;
		case WMDMA:
			SDRAM_CTRL->WEIGHT_WM = weight;
			break;
		default:
			assert(0);
	}
}

