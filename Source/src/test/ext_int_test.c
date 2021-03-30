#include "init.h"
#include "dma.h"

#include "misc.h"
#include "defs.h"
#include "int_handler.h"


extern int feature_load();
extern int pad_set_direction(int);
extern int clk_set(int,int );



volatile int handler_0 = 0;
volatile int handler_1 = 0;
int ext_int_test(){
	 
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


	
		printf(" ext_int init0\n");
		EXT_INT_OUT_CTRL->int2 = 1;


		
		INT_Clear(EXT_INT0_IRQn,0,0);
		INT_Enable(EXT_INT0_IRQn,0,0);
		INT_Clear(EXT_INT1_IRQn,0,0);
		INT_Enable(EXT_INT1_IRQn,0,0);

		EXT_INT_OUT_CTRL->int3 = 1;

		printf(" ext_int init\n");
		
		
		
		while( handler_0 == 0);
			EXT_INT_OUT_CTRL->int2 = 0;
		while( handler_1 == 0);
			EXT_INT_OUT_CTRL->int3 = 0;
			
			

		
		printf("-------------- ext int0/1 test success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("please check waveform of INT2 and INT3 in vcd file, which should rise and then fall");


		/*
		int iiii=0;
		while(1){
			printf("--------------\ success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n");
			iiii += 1;
		}*/
}