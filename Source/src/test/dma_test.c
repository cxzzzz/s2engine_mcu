#include <stdio.h>
#include "CM3DS_MPS2.h"

#include "uart_stdout.h"
#include "CM3DS_MPS2_driver.h"
#include <stdio.h>
#include <string.h>
//#include <assert.h>


#include "defs.h"
#include "dma.h"
#include "int_handler.h"

#include "net.h"

#include "init.h"


int dma_test(){

    clock_init();
    pad_init();
				//配置PAD
		//需要把ie/oen拉高,以把数据改为写模式
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	
	UartStdOutInit();

	dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");

    //两个读时序
	/*
    int b = PPU_CTRL->DC;
	dbg_puts_d("PPU_read:%d",b);
    int a = FMDMA_CTRL->INFO.INFO_0;
	dbg_puts_d("fmdma_read:%d",a);
    //return (a+b);
	*/
		//从ififo到dma
		

		

		
		//启动DMA
		INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
		//INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);

    //关闭IFIFO中断
    
		dma_reset(IFDMA);
		dbg_puts_d("IFDMA reset");
	  dma_config(IFDMA,0,1,0);
    dma_sg_set(IFDMA,0,0x0, 0x10,0x100);
		dbg_puts_d("IFDMA config");
		dbg_puts_d("IFDMA start");
		dma_enable(IFDMA);
		for(int a = 0;a<500;a ++){
				a = a + 1;
		}
		dbg_puts_d("IFDMA start2");
		while(1);
		INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
		return 0;
		
		dma_wait( IFDMA);
		dbg_puts_d("IFDMA stopped");		
		dma_reset(IFDMA);

		

    //测试从sdram到ppu-bm dma(最简单)
    dma_reset( BMDMA);
		dbg_puts_d("BMDMA reset");

    dma_config(BMDMA,0,1,0);
    dma_sg_set(BMDMA,0,0x10, 0x10,0x10);
		dbg_puts_d("BMDMA config");

    dma_enable( BMDMA);
    dbg_puts_d("BMDMA start");
		dma_wait( BMDMA);
		dbg_puts_d("BMDMA stopped");

		return 0;
}
