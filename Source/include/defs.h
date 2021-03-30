
#ifndef _DEFS_H
#define _DEFS_H

#include <stdint.h>
#include <CM3DS_MPS2_driver.h>
#include "config.h"

#include <stdio.h>

#define FPGA_IMAGE

//#define NDEBUG
//#define FASTDEBUG

#ifndef NDEBUG
	#ifdef FASTDEBUG
		#define dbg_puts(fmt,...) printf(fmt,##__VA_ARGS__);
		#define dbg_puts_d(fmt,...) printf(fmt"\n",##__VA_ARGS__);
		#define assert( cond) if( !(cond)) printf("%s:%s:%d: assertion false",__FILE__,__FUNCTION__,__LINE__);
	#else
		#define dbg_puts(fmt,...) printf(fmt,##__VA_ARGS__);
		#define dbg_puts_d(fmt,...) printf("%s:%s:%d:"fmt"\n",__FILE__,__FUNCTION__,__LINE__, ##__VA_ARGS__);
		#define assert( cond) if( !(cond)) printf("%s:%s:%d: assertion false",__FILE__,__FUNCTION__,__LINE__);
	#endif
#else
#define dbg_puts(fmt,...)
#define dbg_puts_d(fmt,...)
#define assert(cond) 
#endif

#define true 1
#define false 0
#define True true
#define False false
	
#define is_true(x) ((x)?1:0)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define BIT(data,b)  ((data)>>(b) & 1) 

#define DMA_MAX_LEN_16



typedef enum{
    IDLE = 0,
    RUNNING = 1,
    END = 2
}MODULE_STATE;


//为了避免被编译器优化（中断和main都可能对参数做出改变),需要增加 volatile

typedef struct {

    volatile int layer_id ;
    volatile LayerConfig* layer_config;

    volatile IOConfig* io_config;
		
		volatile NetConfig* net_config;

		//可能在中断、主线程被使用
    struct{


         MODULE_STATE volatile net_load, //net init
             feature_load,
             wm,
             fm,
             bm, //bbqs mem
             bf,  //bbqs fifo
             wb, //write back
             feature_store; //image_output

    }module_state;

		//仅在中断中被使用？？？
    struct{

        struct{
						int volatile config_outer_cnt;
            int volatile config_cnt;
        }fm; 

        struct{
						int volatile dma_outer_cnt;
            int volatile dma_cnt;
            //int volatile dma_inner_cnt;

        }fmdma;

        struct{
            int volatile dma_cnt;
        }wmdma,bfdma,bmdma,wbdma;

        struct{
            int volatile dma_cnt;
        }net_load,feature_load,feature_store;


    }module_inner_status;

}S2CHIP_STATUS;

extern volatile S2CHIP_STATUS s2chip_status;



#define SDRAM_BASE_ADDR 0x44000000
// size:byte
#define SDRAM_SIZE 0x20000000 


#define WAIT( cond ) do{ dbg_puts_d("wait\n"); while(!(cond)); }while(0)


#define PPU_BASE_ADDR 	0x402b0000

#define PE_BASE_ADDR		0x402a0000

#define DMA_BASE_ADDR		0x40260000

//#define SDRAM_BASE_ADDR	0x40270000

#define FM_BASE_ADDR 		0x40280000

#define WM_BASE_ADDR  	0x40290000

#define CLKGEN_BASE_ADDR	0x40250000

#define PAD_BASE_ADDR	0x40220000

#define NMS_BASE_ADDR 0x402d0000

#define EXT_INT_OUT_BASE_ADDR 0x41000000


////////////////PPU CTRL REG

struct _PPU_CTRL{
	uint32_t BBQS ; //0x0
	uint32_t BBQS_DP ; //0x0
	uint32_t ACT;
	uint32_t POOL ; //0x4
	uint32_t DC;
	//uint32_t RST;
	uint32_t BBQS_CV;
};

extern volatile struct _PPU_CTRL* PPU_CTRL;// = (struct _PPU_CTRL*) PPU_BASE_ADDR ;
#define PPU_BBQS_SYS_LOOP(x)  (x << 0)
#define 	PPU_BBQS_SYS_SC_SIGN(x)		(is_true(x)<<24)
#define		PPU_BBQS_SYS_SC_EN(x)			(is_true(x)<<25)
#define		PPU_BBQS_SYS_EN						(1<<26)
#define     PPU_BBQS_DP_SIZE(x)        ((x)<<0)
#define		PPU_BBQS_DP_STEP(x)	       ((x)<<10)

#define		PPU_ACT_EN(x)	(is_true(x)<<0)

#define 	PPU_POOL_EN(x) 		( is_true(x)<<1)
#define 	PPU_POOL_SIGN(x) 	( is_true(x)<<0)
#define 	PPU_POOL_KERNEL(x)	((x)<<2)

#define		PPU_DC_SIZE(x)	((x)<<0)
#define		PPU_DC_STEP(x)	((x)<<10)

#define   PPU_BBQS_CV_SC_WIDTH(x) 	((x)<<0)
#define		PPU_BBQS_CV_SC_SHIFT(x)  	((x)<<4)
#define		PPU_BBQS_CV_OUT_WIDTH(x)	((x)<<8)
/*#define		PPU_RST_BBQS	(1<<0)
#define		PPU_RST_ACT		(1<<1)
#define		PPU_RST_POOL	(1<<2)
#define		PPU_RST_DC		(1<<3)
*/

////////////////PE CTRL REG

struct _PE_CTRL{
	uint32_t 	COMPRESS;
	uint32_t	CE;
	uint32_t	PE;
};

extern volatile struct _PE_CTRL* 	PE_CTRL;// = (struct _PE_CTRL*)(PE_BASE_ADDR);

#define	PE_COMPRESS_EN(x)	(is_true(x)<<0)

#define	PE_CE_STRIDE(x)	((x)<<0)
#define	PE_CE_KERNEL(x)	((x)<<5)

#define PE_PE_FSIGN(x)	(is_true(x)<<0)
#define PE_PE_OUTDROP(x)	(is_true(x)<<20)

////////////////FM CTRL REG

struct _FM_CTRL{
	uint32_t	CONFIG_KER_STR_POOL_CHN;
	uint32_t	CONFIG_ROW_COL;
	uint32_t	CONFIG_PADDING;
	uint32_t	CONFIG_ROUND;
	uint32_t  INFO_WR_CNT;
	uint32_t  INFO_ERROR;
};

extern volatile struct _FM_CTRL*	FM_CTRL ;//= (struct _FM_CTRL*)(FM_BASE_ADDR);



#define	FM_KERNEL(x) 	((x)<<24)
#define	FM_STRIDE(x)	((x)<<20)
#define	FM_POOLING(x)	((x)<<16)
#define	FM_CHANNEL(x)	((x)<<0)

#define	FM_COL(x)			((x)<<0)
#define	FM_ROW(x)			((x)<<16)

#define	FM_PADDING_TOP(x)			((x)<<24)
#define	FM_PADDING_BOTTOM(x)	((x)<<16)
#define	FM_PADDING_LEFT(x)		((x)<<8)
#define	FM_PADDING_RIGHT(x)		((x)<<0)

#define	FM_ROUND_READ_SIG(x)		((x)<<14)
#define	FM_ROUND_READ_TIMES(x)	((x)<<0)

extern  char fm_new_flag ;
#define FM_NEW_FLAG		((fm_new_flag)<<30)
void fm_new_flag_update(void);


//////////////////WM CTRL REG

struct _WM_CTRL{
	uint32_t	LOOP;
};

extern volatile struct _WM_CTRL* WM_CTRL;// = (struct _WM_CTRL*)(WM_BASE_ADDR);

#define WM_LOOP(x)	((x)<<0)


//////////////////SDRAM CTRL REG
struct _SDRAM_CTRL{
		uint32_t 	WEIGHT_IFIFO;
		uint32_t	WEIGHT_OFIFO;
		uint32_t	WEIGHT_FM;
		uint32_t	WEIGHT_WM;
		uint32_t	WEIGHT_BF;
		uint32_t	WEIGHT_BM;
		uint32_t	WEIGHT_SDRAM;

		//好像这并不是IF,而是M3,不知道为什么走这一路
		//uint32_t	WEIGHT_IFIFO;
		uint32_t	WEIGHT_NONE;
};

extern volatile struct _SDRAM_CTRL* SDRAM_CTRL;// = (struct _SDRAM_CTRL*) SDRAM_BASE_ADDR;



///////////////////CLK_GEN CTRL REG
struct _CLKGEN_CTRL{
	uint32_t N;
	uint32_t M;
	uint32_t PLL_BYPASS;	
	uint32_t OD;

	struct{
		uint32_t	AHB;
		uint32_t	FM;
		uint32_t	WM;
		uint32_t	BBQS;
		uint32_t	ACT;
		uint32_t	POOLING;
		uint32_t	DC;
		uint32_t 	COMPRESS;
		uint32_t 	PE;
		uint32_t 	CE;
		uint32_t 	ALIGNMENT;
		uint32_t	SDRAM;
		uint32_t	DMA;
		uint32_t	FIFO;
		uint32_t	DBGCTL;
	}CLK_SEL;

	struct{
		uint32_t 	N1;
		uint32_t	N2;
		uint32_t	N3;
		uint32_t	N4;
	}DIVIDE;

	struct{
		uint32_t	AHB;
		uint32_t	FM;
		uint32_t	WM;
		uint32_t	BBQS;
		uint32_t  	ACT;
		uint32_t  	POOLING;
		uint32_t  	DC;
		uint32_t  	COMPRESS;
		uint32_t	PE;
		uint32_t  	CE;
		uint32_t  	ALIGNMENt;
		uint32_t  	SDRAM;
		uint32_t  	DMA;
		uint32_t  	FIFO;
		uint32_t  	DBGCTL;
	}RST;

	uint32_t OSC_BYPASS;
};

extern volatile struct _CLKGEN_CTRL* CLKGEN_CTRL;

#define RESET(x)  do{(x) = 1;(x) = 0;}while(0)

/*
struct _RST_CTRL{
	uint32_t	ahb;
	uint32_t	fm;
	uint32_t	wm;
	uint32_t	bbqs;
	uint32_t  act;
	uint32_t  pooling;
	uint32_t  dc;
	uint32_t  compress;
	uint32_t	pe;
	uint32_t  ce;
	uint32_t  alignment;
	uint32_t  sdram;
	uint32_t  dma;
	uint32_t  fifo;
	uint32_t  dbgctl;
};
extern volatile struct _RST_CTRL* RST_CTRL;
*/

//////////////////////////// PAD CTRL REG
struct _PAD_CTRL{

	//uint32_t ioen[(0x50)/ (4)]; // 0x0 -- 0x50 
	struct{
		uint32_t ie1;
		uint32_t oen1;
		uint32_t ie2;
		uint32_t oen2;
		uint32_t ie3_1;
		uint32_t ie3_2;
		uint32_t ie3_3;
		uint32_t ie3_4;
		uint32_t oen3_1;
		uint32_t oen3_2;
		uint32_t oen3_3;
		uint32_t oen3_4;
		uint32_t ie4_1;
		uint32_t ie4_2;
		uint32_t ie4_3;
		uint32_t ie4_4;
		uint32_t oen4_1;
		uint32_t oen4_2;
		uint32_t oen4_3;
		uint32_t oen4_4;
	}ioen;

	uint32_t uart_in_mode;	
	uint32_t bootram_mode;
	uint32_t data_out_mode;
	uint32_t debug_mode;
	
	uint32_t pad_sdram_ds;
	uint32_t power_out;
	uint32_t power_in;

};
extern volatile struct _PAD_CTRL* PAD_CTRL;

struct _NMS_CTRL{
		struct{
				uint32_t x;
				uint32_t y;
				uint32_t h;
				uint32_t w;
				uint32_t c;
				uint32_t cls;
		}factor;
		
		struct{
				struct{
					uint32_t xmax;
					uint32_t ymax;
					uint32_t nmax;
				}post;
				struct{
						uint32_t xmax;
						uint32_t ymax;
				}orig;
				struct{
						uint32_t x;
						uint32_t y;
				}scale;
				
		}image;
		
		struct{
				struct{
						uint32_t h;
						uint32_t w;
				} anchors[8];
		}anchor;
		
		struct{
				uint32_t chance;
				uint32_t iou;
		}threshold;
};
extern volatile struct _NMS_CTRL* NMS_CTRL;

struct _EXT_INT_OUT_CTRL{
	uint32_t int2; 
	uint32_t int3;
};
extern volatile struct _EXT_INT_OUT_CTRL *EXT_INT_OUT_CTRL;

struct _SDRAM{
	uint32_t data[ SDRAM_SIZE/4 ];
};

extern volatile struct _SDRAM *SDRAM;


/*
void int_enable( IRQn_Type interrupt){
    //-> 上升沿触发
    NVIC_SetPriority(interrupt,0xc);
    NVIC_ClearPendingIRQ(interrupt);
    NVIC_EnableIRQ(interrupt);
}

void int_disable( IRQn_Type interrupt){

    NVIC_ClearPendingIRQ(interrupt);
    NVIC_DisableIRQ(interrupt);
}
*/

#endif

//          
