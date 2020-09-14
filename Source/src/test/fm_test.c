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

int fm_test(){

    clock_init();
    pad_init();
	UartStdOutInit();
	dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");



    //配置fm寄存器

    FM_CTRL->CONFIG_KER_STR_POOL_CHN = FM_NEW_FLAG | FM_KERNEL(3) | FM_STRIDE(1) | FM_POOLING(1) | FM_CHANNEL(2);

    FM_CTRL->CONFIG_ROW_COL = FM_NEW_FLAG | FM_COL(16) | FM_ROW(16);

    FM_CTRL->CONFIG_PADDING = FM_NEW_FLAG | FM_PADDING_TOP(1) | FM_PADDING_BOTTOM(1) | FM_PADDING_LEFT(1) | FM_PADDING_RIGHT(1);

    FM_CTRL->CONFIG_ROUND = FM_NEW_FLAG | FM_ROUND_READ_SIG(0) | FM_ROUND_READ_TIMES(0);

    fm_new_flag_update();

    //向fm搬运数据

    dma_reset( FMDMA);
	dbg_puts_d("FMDMA reset");

    //设置fm end = 1;
    dma_config(FMDMA,0,1,1);
    dma_sg_set(FMDMA,0,0x100, 0x0,16*16*16);
	dbg_puts_d("FMDMA config");

    dma_enable( FMDMA);
    dbg_puts_d("FMDMA start");

    //fm启动
    //可能是数据足够了自动启动?

		return 0;
}
