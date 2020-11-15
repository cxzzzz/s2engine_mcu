#include "defs.h"
#include "int_handler.h"

#include "net.h"

#include "init.h"
#include "uart_stdout.h"


int basic_test(void){
	clock_init();
    pad_init();
	
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	
		UartStdOutInit();
		dbg_puts_d("success!!!!!!!!!!!!!!!!!!!!!!!!!!");
	
		return 0;
}