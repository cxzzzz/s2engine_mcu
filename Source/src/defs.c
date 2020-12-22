
#include "defs.h"



volatile S2CHIP_STATUS s2chip_status;

volatile struct _PPU_CTRL* PPU_CTRL = (struct _PPU_CTRL*) PPU_BASE_ADDR ;
volatile struct _PE_CTRL* 	PE_CTRL = (struct _PE_CTRL*)(PE_BASE_ADDR);
volatile struct _FM_CTRL*	FM_CTRL = (struct _FM_CTRL*)(FM_BASE_ADDR);
volatile struct _WM_CTRL* WM_CTRL = (struct _WM_CTRL*)(WM_BASE_ADDR);
volatile struct _SDRAM_CTRL* SDRAM_CTRL = (struct _SDRAM_CTRL*) SDRAM_BASE_ADDR;

volatile struct _PAD_CTRL* PAD_CTRL = (struct _PAD_CTRL*)(PAD_BASE_ADDR);

volatile struct _CLKGEN_CTRL* CLKGEN_CTRL = (struct _CLKGEN_CTRL*)( CLKGEN_BASE_ADDR);

volatile struct _NMS_CTRL* NMS_CTRL = (struct _NMS_CTRL *)(NMS_BASE_ADDR);

char fm_new_flag = 01;

void fm_new_flag_update(void){
    fm_new_flag = (~fm_new_flag) & 3;
}



