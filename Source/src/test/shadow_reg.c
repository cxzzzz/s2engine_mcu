#include "shadow_reg.h"

struct _PPU_CTRL SHADOW_PPU_CTRL;

struct _PE_CTRL  SHADOW_PE_CTRL;

struct _FM_CTRL  SHADOW_FM_CTRL;

struct _WM_CTRL  SHADOW_WM_CTRL;

struct _SDRAM_CTRL SHADOW_SDRAM_CTRL;


//提前生成影子寄存器参数，以节约向寄存器写入的周期
void load_shadow_regs(){

}
