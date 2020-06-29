#ifndef INT_HANDLER_H
#define INT_HANDLER_H

#include "defs.h"
#include "CM3DS_MPS2.h"


//  INTERRUPT

//#define WM_IRQ GPIO0_1_IRQn
//#define BM_IRQ GPIO0_2_IRQn
//#define BF_IRQ GPIO0_3_IRQn

#define FM_IRQ      PORT0_0_IRQn
#define FM_IRQ_HANDLER PORT0_0_Handler
#define FM_INT_IO		CM3DS_MPS2_GPIO0
#define FM_INT_PORT	0

#define FMDMA_IRQ  		PORT0_1_IRQn
#define FMDMA_IRQ_HANDLER 	PORT0_1_Handler
#define FMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define FMDMA_INT_PORT	1

#define WMDMA_IRQ   PORT0_2_IRQn
#define WMDMA_IRQ_HANDLER 	PORT0_2_Handler
#define WMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define WMDMA_INT_PORT	2
 
#define BMDMA_IRQ   PORT0_3_IRQn
#define BMDMA_IRQ_HANDLER 	PORT0_3_Handler
#define BMDMA_INT_IO	CM3DS_MPS2_GPIO0
#define BMDMA_INT_PORT	3


#define BFDMA_IRQ   PORT0_4_IRQn
#define BFDMA_IRQ_HANDLER 	PORT0_4_Handler
#define BFDMA_INT_IO	CM3DS_MPS2_GPIO0
#define BFDMA_INT_PORT	4

#define WBDMA_IRQ   PORT0_5_IRQn
#define WBDMA_IRQ_HANDLER 	PORT0_5_Handler
#define WBDMA_INT_IO	CM3DS_MPS2_GPIO0
#define WBDMA_INT_PORT	5

#define IFDMA_IRQ   PORT0_6_IRQn
#define IFDMA_IRQ_HANDLER 	PORT0_6_Handler
#define IFDMA_INT_IO	CM3DS_MPS2_GPIO0
#define IFDMA_INT_PORT	6

#define OFDMA_IRQ   PORT0_7_IRQn
#define OFDMA_IRQ_HANDLER 	PORT0_7_Handler
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



