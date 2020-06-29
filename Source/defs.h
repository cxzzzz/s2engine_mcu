
#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include <CM3DS_MPS2_driver.h>
#include "config.h"

#include <stdio.h>

#ifndef NDEBUG
#define dbg_puts(fmt,...) printf(fmt,##__VA_ARGS__)
#define dbg_puts_d(fmt,...) printf("%s %s %d:"fmt"\n",__FILE__,__FUNCTION__,__LINE__, ##__VA_ARGS__)
#else
#define dbg_puts(fmt,...)
#define dbg_puts_d(fmt,...)
#endif

#define true 1
#define false 0
#define True true
#define False false
	
#define is_true(x) ((x)?1:0)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))



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
            int volatile dma_inner_cnt;

        }fmdma;

        struct{
            int volatile dma_cnt;
        }wmdma,bfdma,bmdma,wbdma;

        struct{
            int volatile dma_cnt;
        }net_load,feature_load,feature_store;


    }module_inner_status;

}S2CHIP_STATUS;

extern S2CHIP_STATUS s2chip_status;




#define WAIT( cond ) while(!(cond)){ }


#define PPU_BASE_ADDR 0x100

#define PE_BASE_ADDR 0x200

#define DMA_BASE_ADDR 0x300 

#define SDRAM_BASE_ADDR 0x400

#define FM_BASE_ADDR 0x500

#define WM_BASE_ADDR 0x600




////////////////PPU CTRL REG

struct _PPU_CTRL{
	uint32_t BBQS ; //0x0
	uint32_t ACT;
	uint32_t POOL ; //0x4
	uint32_t DC;
	uint32_t RST;
};

extern struct _PPU_CTRL* PPU_CTRL;// = (struct _PPU_CTRL*) PPU_BASE_ADDR ;
#define PPU_BBQS_SYS_LOOP(x)  (is_true(x)<< 0)
#define 	PPU_BBQS_SYS_SC_SIGN(x)		(is_true(x)<<23)
#define		PPU_BBQS_SYS_SC_EN(x)			(is_true(x)<<24)

#define		PPU_ACT_EN(x)	(is_true(x)<<23)

#define 	PPU_POOL_EN(x) 		( is_true(x)<<1)
#define 	PPU_POOL_SIGN(x) 	( is_true(x)<<0)
#define 	PPU_POOL_KERNEL(x)	((x)<<2)

#define		PPU_DC_SIZE(x)	((x)<<0)
#define		PPU_DC_STEP(x)	((x)<<10)

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

extern struct _PE_CTRL* 	PE_CTRL;// = (struct _PE_CTRL*)(PE_BASE_ADDR);

#define	PE_COMPRESS_EN(x)	(is_true(x)<<0)

#define	PE_CE_STRIDE(x)	((x)<<0)
#define	PE_CE_KERNEL(x)	((x)<<5)

#define PE_PE_FSIGN(x)	(is_true(x)<<0)

////////////////FM CTRL REG

struct _FM_CTRL{
	uint32_t	CONFIG_KER_STR_POOL_CHN;
	uint32_t	CONFIG_ROW_COL;
	uint32_t	CONFIG_PADDING;
	uint32_t	CONFIG_ROUND;
};

extern struct _FM_CTRL*	FM_CTRL ;//= (struct _FM_CTRL*)(FM_BASE_ADDR);

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


//////////////////WM CTRL REG

struct _WM_CTRL{
	uint32_t	LOOP;
};

extern struct _WM_CTRL* WM_CTRL;// = (struct _WM_CTRL*)(WM_BASE_ADDR);

#define WM_LOOP(x)	((x)<<0)


//////////////////SDRAM CTRL REG
struct _SDRAM_CTRL{
		uint32_t	WEIGHT_FM;
		uint32_t	WEIGHT_BM;
		uint32_t	WEIGHT_BF;
		uint32_t	WEIGHT_WM;
		uint32_t	WEIGHT_IFIFO;
		uint32_t	WEIGHT_SDRAM;
		uint32_t	WEIGHT_OFIFO;
};

extern struct _SDRAM_CTRL* SDRAM_CTRL;// = (struct _SDRAM_CTRL*) SDRAM_BASE_ADDR;

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
