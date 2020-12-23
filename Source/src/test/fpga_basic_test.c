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
	
	
			//��߲�������Ƶ��

		//�����þ������ dmaƵ����������ݹ�Ӧ�ٶȣ�ͬʱ����macƵ������߼��ٱ�
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core��Ƶ
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma��Ƶ
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu��Ƶ


		
		clk_set(0,0);
		printf("clk init\n");
		
		printf("--------------m3 boot success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n");
}