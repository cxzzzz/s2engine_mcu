
#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include "defs.h"


typedef enum {  //地址作为ID
	IFDMA	= 0x40260000,
	OFDMA 	= 0x40260100,
	FMDMA 	= 0x40260200,
	WMDMA 	= 0x40260300,
	BFDMA 	= 0x40260400,
	BMDMA 	= 0x40260500,
	WBDMA 	= 0x40260600,
	ODIDMA  = 0x40260700,
	ODODMA  = 0x40260800
}DMA_ID;


extern const char* GET_DMA_NAME(DMA_ID id);
/*
#define FM_DMA  0
#define WM_DMA  1
#define BF_DMA  2
#define BM_DMA  3
#define WB_DMA   4
#define IF_DMA   5
#define OF_DMA   6
*/

#define DMA_SG_MAX 16

typedef struct _DMA_CTRL{
	union{
		struct{
			uint32_t CONFIG_START;
			uint32_t CONFIG_TE_SG_FMEND;
			uint32_t CONFIG_TIMER;
			uint32_t RESET;
		}CTRL;
		struct{
			uint32_t INFO_0;
			uint32_t INFO_1;
			uint32_t INFO_2;
			uint32_t INFO_3;
		}INFO;
	};

	uint32_t VOID[4];
	
	//sg reg
	struct{
		uint32_t RD_ADDR;
		union{
			uint32_t WR_ADDR;
			uint32_t SG_EXT;
		};
		uint32_t LEN;
	}CONFIG_DMA[DMA_SG_MAX];
	
}DMA_CTRL;

#define SG_EXT_LOOP(x) ((x) << 24)
#define SG_EXT_STEP(x) ((x) << 0)

struct _DMA_INFO{
	uint32_t INFO_0;
	uint32_t INFO_1;
	uint32_t INFO_2;
	uint32_t INFO_3;
};

extern  struct _DMA_INFO DMA_INFO;

extern volatile DMA_CTRL* FMDMA_CTRL;
extern volatile DMA_CTRL* WMDMA_CTRL;
extern volatile DMA_CTRL* BFDMA_CTRL;
extern volatile DMA_CTRL* BMDMA_CTRL;
extern volatile DMA_CTRL* WBDMA_CTRL;
extern volatile DMA_CTRL* IFDMA_CTRL;
extern volatile DMA_CTRL* OFDMA_CTRL;

extern volatile DMA_CTRL* ODIDMA_CTRL;
extern volatile DMA_CTRL* ODODMA_CTRL;

#define DMA_START(x) (is_true(x) << 0);
#define DMA_TIMER_EN(x) (is_true(x) << 7);


void dma_config(DMA_ID dma, uint32_t timer,uint8_t sg_num,uint8_t fm_end); //0为不设置计时器

void dma_reset(DMA_ID dma);

int dma_int_clear(DMA_ID dma);

void dma_sg_set(DMA_ID dma,uint8_t sg_idx,uint32_t rd_addr,uint32_t wr_addr,uint32_t len);
void dma_sg_ext_set( DMA_ID dma,uint8_t sg_idx,uint32_t rd_addr,uint32_t size , uint32_t step , uint32_t loop );
	
void dma_enable(DMA_ID dma);

void dma_weight_set(DMA_ID dma,int weight);

int dma_wait(DMA_ID dma);

#endif
