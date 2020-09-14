#include <stdio.h>
#include "CM3DS_MPS2.h"

#include "uart_stdout.h"
#include "CM3DS_MPS2_driver.h"
#include <stdio.h>
#include <string.h>
//#include <assert.h>


#include "defs.h"
#include "dma.h"
#include "int_handler.h"

#include "net.h"

#include "init.h"

int wm_test(){

    clock_init();
    pad_init();
	UartStdOutInit();
	dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");

    //配置wm寄存器
    WM_CTRL->LOOP = 0x10;
	//WM_CTRL->LOOP = WM_LOOP(s2chip_status.layer_config->wm.loop);

    dbg_puts_d("WM config");

    //向wm搬运数据
    dma_reset( WMDMA);
	dbg_puts_d("WMDMA reset");

    dma_config(WMDMA,0,1,0);
    dma_sg_set(WMDMA,0,0x100, 0x0,0x200);
	dbg_puts_d("WMDMA config");

    dma_enable( WMDMA);
    dbg_puts_d("WMDMA start");
		
		return 0;
}
