#include "init.h"
#include "dma.h"

#include "misc.h"


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
	
	
		/*UartStdOutInit();
		printf("fast uart init\n");
		printf("fast uart init\n");
	*/
	
		UartStdOutInit();
		uart_init(75.0, 38400);
	
		printf("slow uart init0\n");
		printf("slow uart init1\n");

		printf("slow uart init2\n");
		printf("slow uart init3\n");

		/*
		UartStdOutInit();
		printf("fast uart init\n");
		printf("fast uart init\n");
	*/

	
		/*
			//��߲�������Ƶ��

		//�����þ������ dmaƵ����������ݹ�Ӧ�ٶȣ�ͬʱ����macƵ������߼��ٱ�
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core��Ƶ
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma��Ƶ
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu��Ƶ
		*/


		
		//clk_set(0,0);
		//printf("clk init\n");
		int iiii=0;
		while(1){
			printf("--------------m3 boot success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n");
			iiii += 1;
		}
}