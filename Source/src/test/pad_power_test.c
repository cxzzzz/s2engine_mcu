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
int pad_power_test(){
	 
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	

		UartStdOutInit();
		printf("uart init");
	
	
			//��߲�������Ƶ��

		//�����þ������ dmaƵ����������ݹ�Ӧ�ٶȣ�ͬʱ����macƵ������߼��ٱ�
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core��Ƶ
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma��Ƶ
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu��Ƶ


		
		clk_set(0,0);
		printf("clk init");
	
		//����PE���
	
		int t;
		
		t = PAD_CTRL->pad_sdram_ds;
		printf("read pad_sdram_ds:%d\n",t);
		t = PAD_CTRL->power_out;
		printf("read pad_power_out:%d\n",t);
		
		t = PAD_CTRL->power_in;
		printf("read pad_power_in:%d\n",t);

		
		PAD_CTRL->pad_sdram_ds = 2;
		PAD_CTRL->power_out = 123432;
		PAD_CTRL->power_in  = 432133;
		
		t = PAD_CTRL->pad_sdram_ds;
		printf("read pad_sdram_ds:%d\n",t);
		t = PAD_CTRL->power_out;
		printf("read pad_power_out:%d\n",t);
		t = PAD_CTRL->power_in;
		printf("read pad_power_in:%d\n",t);

		printf("end\n");
		printf("end\n");
		printf("end\n");
		printf("end\n");


}