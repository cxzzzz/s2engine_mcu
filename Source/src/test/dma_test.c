#include <stdio.h>
#include "CM3DS_MPS2.h"

#include "uart_stdout.h"
#include "CM3DS_MPS2_driver.h"
#include "CM3DS_function.h"
#include <stdio.h>
#include <string.h>
//#include <assert.h>


#include "defs.h"
#include "int_handler.h"

#include "net.h"

#include "init.h"


int dma_test(){

    pad_init();
	UartStdOutInit();
	dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");

    //测试从sdram到ppu-bm dma(最简单)
    dma_reset( BMDMA);
	dbg_puts_d("BMDMA reset");

    dma_config(BMDMA,0,1,sg_num);
    dma_sg_set(dma,0,0x100, 0x000,0x20);
	dbg_puts_d("BMDMA config");

    dma_enable( BMDMA);
    dbg_puts_d("BMDMA start");

}