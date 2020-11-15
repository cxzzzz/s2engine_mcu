
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


extern void feature_load(void);
extern void feature_store(void);

int ofifo_test(void){
	    clock_init();
    pad_init();
	
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
		dbg_puts_d("pad input");
	
		UartStdOutInit();
		dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");
	
	

    net_init();
		dbg_puts_d("net init");
	
		 feature_load();
		 dbg_puts_d("feature loaded");
	
		PAD_CTRL->ioen.ie1 = 0;
		PAD_CTRL->ioen.oen1 = 0;
		
		dbg_puts_d("pad output");
		
		
			net_io.feature_store.dma_length = net_io.feature_load.dma_length;
			net_io.feature_store.dma = net_io.feature_load.dma;
		 feature_store();
		 dbg_puts_d("feature stored");
	
	return 0;
}