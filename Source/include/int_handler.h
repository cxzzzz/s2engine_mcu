#ifndef INT_HANDLER_H
#define INT_HANDLER_H

#include "defs.h"
#include "CM3DS_MPS2.h"


//  INTERRUPT

//#define WM_IRQ GPIO0_1_IRQn
//#define BM_IRQ GPIO0_2_IRQn
//#define BF_IRQ GPIO0_3_IRQn

#define FM_IRQ      64
#define FM_IRQ_HANDLER FM_IRQ_Handler
#define FM_INT_IO		CM3DS_MPS2_GPIO0
#define FM_INT_PORT	0

#define FMDMA_IRQ  	61
#define FMDMA_IRQ_HANDLER 	FMDMA_IRQ_Handler
#define FMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define FMDMA_INT_PORT	1

#define WMDMA_IRQ   60
#define WMDMA_IRQ_HANDLER 	WMDMA_IRQ_Handler
#define WMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define WMDMA_INT_PORT	2
 
#define BMDMA_IRQ  	58
#define BMDMA_IRQ_HANDLER 	BMDMA_IRQ_Handler
#define BMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define BMDMA_INT_PORT	3


#define BFDMA_IRQ   59
#define BFDMA_IRQ_HANDLER 	BFDMA_IRQ_Handler
#define BFDMA_INT_IO	CM3DS_MPS2_GPIO0
#define BFDMA_INT_PORT	4

#define WBDMA_IRQ   57
#define WBDMA_IRQ_HANDLER 	WBDMA_IRQ_Handler
#define WBDMA_INT_IO	CM3DS_MPS2_GPIO0
#define WBDMA_INT_PORT	5

#define IFDMA_IRQ   63
#define IFDMA_IRQ_HANDLER 	IFDMA_IRQ_Handler
#define IFDMA_INT_IO	CM3DS_MPS2_GPIO0
#define IFDMA_INT_PORT	6

#define OFDMA_IRQ   62
#define OFDMA_IRQ_HANDLER 	OFDMA_IRQ_Handler
#define OFDMA_INT_IO	CM3DS_MPS2_GPIO0
#define OFDMA_INT_PORT	7

/*#define INT_HANDLER(interrupt) \
    void interrupt##_handler(void)

#define CALL_INT_HANDLER(interrupt) \
    interrupt##_handler()
		*/


void  int_init(void);
		
void INT_Disable(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port);

void INT_Clear(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port);
		
void INT_Enable(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port);

/*
INT_HANDLER(FM_IRQ);

INT_HANDLER(FMDMA_IRQ);
INT_HANDLER(WMDMA_IRQ);
INT_HANDLER( BFDMA_IRQ);
INT_HANDLER( BMDMA_IRQ);
INT_HANDLER( WBDMA_IRQ);

INT_HANDLER(IFDMA_IRQ);
INT_HANDLER(OFDMA_IRQ);
*/

void FM_IRQ_HANDLER(void);
void FMDMA_IRQ_HANDLER(void);
void WMDMA_IRQ_HANDLER(void);
void BFDMA_IRQ_HANDLER(void);
void BMDMA_IRQ_HANDLER(void);
void WBDMA_IRQ_HANDLER(void);
void IFDMA_IRQ_HANDLER(void);
void OFDMA_IRQ_HANDLER(void);

#endif



