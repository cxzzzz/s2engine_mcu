
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


extern void feature_load();
extern void feature_store();

extern void layer_init(int layer);

extern void layer_run(int layer);

extern void pad_set_direction(int input);


extern void clk_set(int core_clk, int peri_clk);

int int_0_flag;
int int_1_flag;

void fpga_feature_store(){
		// set int_2;
		// wait int_0;
	
		int_0_flag = 0;
		INT_Enable(EXT_INT0_IRQn,0,0);
		EXT_INT_OUT_CTRL->int2 = 0;
		EXT_INT_OUT_CTRL->int2 = 1;
		WAIT(int_0_flag != 0);
		EXT_INT_OUT_CTRL->int2 = 0;
		feature_store();
	
}

int fpga_s2chip(){
	
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	

		UartStdOutInit();
		uart_init(75.0, 38400);
	
		printf("slow uart init0\n");
		dbg_puts_d("uart init");
	
	
			//提高部分区域频率
	
			/*
		N1: core分频
		N2: sdram分频
		N3: mac分频
		*/

		/*
		//该配置尽量提高 dma频率以提高数据供应速度，同时降低mac频率以提高加速比
		CLKGEN_CTRL->DIVIDE.N2 = 8; 
		CLKGEN_CTRL->DIVIDE.N1 = 9;
		CLKGEN_CTRL->DIVIDE.N3 = 30;
		*/
			
			/*

		//该配置尽量提高 总体频率，以提高吞吐量
		CLKGEN_CTRL->DIVIDE.N2 = 8; 
		CLKGEN_CTRL->DIVIDE.N1 = 2;
		CLKGEN_CTRL->DIVIDE.N3 = 3;
		*/
		

		//clk_set(0,0);
		
		
		dbg_puts_d("clk init");
		
		
		
	
		//丢弃PE输出
				
			
			s2chip_init();
			dbg_puts_d("s2chip init");
		
			/*
			pad_set_direction(0);
			for(uint32_t i = 0 ; i < 256; i+=4)
					{
							volatile uint32_t* addr = (uint32_t*)(0x60000000+s2chip_status.io_config->feature_store.dma[0].rd_addr + i);
							*addr = i;
						
							//printf("%x:\t%x\n",i,data);
					}
			
			fpga_feature_store();
			WAIT(0);
			*/
			

			net_init();
			dbg_puts_d("net init");
			
	
	
    while(true){
			
				pad_set_direction(1);

        
        feature_load();
				dbg_puts_d("feature loaded");
			
				
        for(int layer = 0; layer < s2chip_status.net_config->layer_length;layer ++){
						//printf(">>>>>>>>>>> layer %d start <<<<<<<<<<<\n",layer);
            layer_run(layer);
						//dbg_puts_d("layer %d done",layer);
						//printf(">>>>>>>>>>> layer %d done <<<<<<<<<<<\n",layer);
        }
				
				pad_set_direction(0);
				
				dbg_puts_d("calculate end\nprint output\n");
				
				/*
				{
					
				
					//for(uint32_t i = 0 ; i < s2chip_status.io_config->feature_store.dma[0].size ; i+=4)
					for(uint32_t i = 0 ; i < 1024; i+=4)
					{
							uint32_t* addr = (uint32_t*)(0x60000000+s2chip_status.io_config->feature_store.dma[0].rd_addr + i);
							uint32_t data = *addr;
						
							printf("%x:\t%x\n",i,data);
					}
				
				}
				*/
				
				

				fpga_feature_store();
				dbg_puts_d("feature stored");		
				
				printf(">>>>>>>>>> output done >>>>>>>>>>>>>>>>>>>>\n");
    }
}
