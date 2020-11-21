
#include "net.h"
#include "defs.h"
#include "int_handler.h"
#include "init.h"



void pad_init(){

/*
  HW32_REG(PAD_BASE_ADDR + 0x50) = 0x01 ;//UART_IN_MODE
  HW32_REG(PAD_BASE_ADDR + 0x58) = 0x01 ;//DATA_OUT_MODE
  HW32_REG(PAD_BASE_ADDR + 0x5c) = 0x00 ;//DEBUG_MODE
  */

  PAD_CTRL->uart_in_mode = 0x01; //使能uart
  /*
  PAD_CTRL->data_out_mode = 0x01;
  PAD_CTRL->debug_mode  = 0x00;
  */

}

void clock_init(){
  //至少需要初始化分频系数，否则无法产生时钟信号
	//通过设置寄存器初始值，已经不需要初始化
	
	/*
  CLKGEN_CTRL->DIVIDE.N1 = 4;
  CLKGEN_CTRL->DIVIDE.N2 = 4;
  CLKGEN_CTRL->DIVIDE.N3 = 4;
  CLKGEN_CTRL->DIVIDE.N4 = 4;
	*/

}


void s2chip_init(){
	s2chip_status.net_config = &net;
	s2chip_status.io_config = &net_io;
  

	dbg_puts_d("int init start");
	int_init();
	dbg_puts_d("int init done");
}

// 将Net数据Load到片上
void net_init(){
    s2chip_status.module_state.net_load = RUNNING;
		s2chip_status.module_inner_status.net_load.dma_cnt = 0;
    //使能IFIFO中断
    
	
		INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
	
		//printf("hello");

    //搬运数
    //CALL_INT_HANDLER(IFDMA_IRQ);
		IFDMA_IRQ_HANDLER();

    //等待数据搬运完成
    WAIT( s2chip_status.module_state.net_load == END);

    //关闭IFIFO中断
    INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
}
