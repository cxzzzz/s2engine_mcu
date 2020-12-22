#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "CM3DS_MPS2.h"

#include "uart_stdout.h"
#include "CM3DS_MPS2_driver.h"

#include <stdio.h>
#include <string.h>
//#include <assert.h>


#include "defs.h"
#include "int_handler.h"

#include "net.h"

#include "init.h"
#include "dma.h"



extern int feature_load();
extern int pad_set_direction(int);
extern int clk_set(int,int );
int nms_test(){
	 
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	

		UartStdOutInit();
		printf("uart init");
	
	
			//提高部分区域频率

		//该配置尽量提高 dma频率以提高数据供应速度，同时降低mac频率以提高加速比
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core分频
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma分频
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu分频


		
		clk_set(0,0);
		printf("clk init");
	
		//丢弃PE输出
	

    s2chip_init();
		printf("s2chip init");
	
	

    net_init();
		printf("net init");

	
   
				pad_set_direction(1);
        
        feature_load();
				printf("feature loaded");
		
	
		NMS_CTRL->factor.c = 123;
		NMS_CTRL->factor.cls= 456;
		NMS_CTRL->factor.h= 789;
		NMS_CTRL->factor.w= 345;
		NMS_CTRL->factor.x= 3456;
		NMS_CTRL->factor.y= 125;
		
		
		for(int i = 0 ;i<8;i++){
			NMS_CTRL->anchor.anchors[i].h = 12;
			NMS_CTRL->anchor.anchors[i].w = 12;
		}
		NMS_CTRL->image.orig.xmax = 8;
		NMS_CTRL->image.orig.ymax = 8;
		NMS_CTRL->image.post.xmax = 4;
		NMS_CTRL->image.post.ymax = 4;
		NMS_CTRL->image.post.nmax = 4;
		NMS_CTRL->threshold.chance = 3;
		NMS_CTRL->threshold.iou = 2;
		
		printf("nms init");
		
		dma_config( ODIDMA, 0, 1, 0 ); 
		dma_sg_set( ODIDMA,0,0,0,0x4000);
		dma_enable( ODIDMA);
		
		printf("input dma init");
		
		dma_config( ODODMA, 0, 1, 0 ); 
		dma_sg_set( ODODMA,0,0,0,0x4000);
		dma_enable( ODODMA);
		
		printf("output dma init");
}