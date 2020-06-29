
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

DMA_CTRL* FMDMA_CTRL = (DMA_CTRL*)FMDMA;
DMA_CTRL* WMDMA_CTRL = (DMA_CTRL*)WMDMA;
DMA_CTRL* BFDMA_CTRL = (DMA_CTRL*)BFDMA;
DMA_CTRL* BMDMA_CTRL = (DMA_CTRL*)BMDMA;
DMA_CTRL* WBDMA_CTRL = (DMA_CTRL*)WBDMA;
DMA_CTRL* IFDMA_CTRL = (DMA_CTRL*)IFDMA;
DMA_CTRL* OFDMA_CTRL = (DMA_CTRL*)OFDMA;

#define bits_assign(high,low,value)  ( value<<(low) )

void dma_config(DMA_ID dma, uint32_t timer,uint8_t sg_num,uint8_t fm_end){
	uint32_t v = 0;
	if(timer != 0){
		v = v | bits_assign(7,7,1);
		*( ((uint32_t*)dma) + 0x2) = timer;
	}
	v = v | bits_assign( 5,0 , sg_num );
	
	if( fm_end != 0)
		v = v | bits_assign( 6,6,1);
	
	*( ((uint32_t*)dma) + 0x1 ) =  v;
}


void dma_reset(DMA_ID dma){
	*(((uint32_t*)dma)+ 0x3) = 1;
}

inline void dma_sg_set(DMA_ID dma,uint8_t sg_idx,uint32_t rd_addr,uint32_t wr_addr,uint32_t len){
	uint32_t* dma_addr = ((uint32_t*)(dma)) + (0x8 * 4) + (sg_idx * 3);
	*(dma_addr + 0) = rd_addr;
	*(dma_addr + 1) = wr_addr;
	*(dma_addr + 2) = len;
}



inline void dma_int_clear(DMA_ID dma){
	//读取info0 时会清除dma中断
	uint32_t info = *( ((uint32_t*)dma) + 0x0 );
}
	
inline void dma_enable(DMA_ID dma){
	*( ((uint32_t*) dma) + 0 )  = 1;
}
