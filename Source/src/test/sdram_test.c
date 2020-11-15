
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

//#define HW32_REG(ADDRESS)  (*((volatile unsigned long  *)(ADDRESS)))

#define SDRAM_MEM_BASE_ADDR 0x00400000
int sdram_test(){

	  clock_init();
    pad_init();
	
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	
		UartStdOutInit();
		dbg_puts_d("uart init");
	
		for( int i = 0; i < 15 ; i ++ ){
			dbg_puts_d("sdram:%p write start", (int*)(SDRAM_MEM_BASE_ADDR) + i );
			*((int*)(SDRAM_MEM_BASE_ADDR) + i) =  i*1001;
			dbg_puts_d("sdram:%p write:%d", (int*)(SDRAM_MEM_BASE_ADDR) + i, i*1001);
		}
		for( int i = 0; i < 15 ; i ++ ){
			int t = *((int*)(SDRAM_MEM_BASE_ADDR) + i);
			dbg_puts_d("sdram:%p read:%d", (int*)(SDRAM_MEM_BASE_ADDR) + i, t);
		}
		
	return 0;
}
