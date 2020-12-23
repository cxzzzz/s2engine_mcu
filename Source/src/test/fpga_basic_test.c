#include "init.h"
#include "dma.h"



extern int feature_load();
extern int pad_set_direction(int);
extern int clk_set(int,int );
int fpga_basic_test(){
	 
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	

		UartStdOutInit();
		printf("uart init\n");
	
	
			//提高部分区域频率

		//该配置尽量提高 dma频率以提高数据供应速度，同时降低mac频率以提高加速比
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core分频
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma分频
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu分频


		
		clk_set(0,0);
		printf("clk init\n");
		
		printf("--------------m3 boot success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n");
}