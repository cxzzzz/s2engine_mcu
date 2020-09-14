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

//
int bm_end = 0;
/*
void BMDMA_IRQ_HANDLER(){
    bm_end = 1;
}
*/

int ppu_test(){

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

    //向bm搬运数据
    dma_reset( BMDMA );
	dbg_puts_d("BMDMA reset");

    dma_config(BMDMA,0,1,1);
    dma_sg_set(BMDMA,0,0x100,0x0,16*16*16);
	dbg_puts_d("BMDMA config");
    dma_enable( BMDMA);
    dbg_puts_d("BMDMA start");

    while(!bm_end);



    //向fm搬运数据

    dma_reset( FMDMA);
	dbg_puts_d("FMDMA reset");

    //设置fm end = 1;
    dma_config(FMDMA,0,1,1);
    dma_sg_set(FMDMA,0,0x100, 0x0,16*16*16);
	dbg_puts_d("FMDMA config");

    //可能是数据足够了自动启动?


    //配置pe
    //配置compress不压缩
    //配置ce
    //配置pe
    PE_CTRL->CE = PE_CE_KERNEL( 2 ) | PE_CE_STRIDE(1);
    PE_CTRL->COMPRESS = PE_COMPRESS_EN(0);
    PE_CTRL->PE = PE_PE_FSIGN(1);

    PPU_CTRL->ACT =  PPU_ACT_EN(1);
    PPU_CTRL->BBQS = PPU_BBQS_SYS_LOOP(0) | PPU_BBQS_SYS_SC_EN(0) | PPU_BBQS_SYS_SC_SIGN(1);
    PPU_CTRL->BBQS_DP = PPU_BBQS_DP_SIZE(1) | PPU_BBQS_DP_STEP(1);
    PPU_CTRL->BBQS_CV = PPU_BBQS_CV_OUT_WIDTH(0) | PPU_BBQS_CV_SC_SHIFT(1) | PPU_BBQS_CV_SC_WIDTH(0);
    PPU_CTRL->DC = PPU_DC_SIZE(1) | PPU_DC_STEP(1);
    PPU_CTRL->POOL = PPU_POOL_EN(0) | PPU_POOL_KERNEL(2) | PPU_POOL_SIGN(0);

    dma_enable( FMDMA);
    dbg_puts_d("FMDMA start");

    //向bf搬运数据
    dma_reset( BFDMA);
	dbg_puts_d("BFDMA reset");

    dma_config(BFDMA,0,1,1);
    dma_sg_set(BFDMA,0,0x100, 0x0,16*16*16);
	dbg_puts_d("BFDMA config");
	
		return 0;

}
