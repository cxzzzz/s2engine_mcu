#include "defs.h"


extern struct _PPU_CTRL SHADOW_PPU_CTRL;

extern struct _PE_CTRL  SHADOW_PE_CTRL;

extern struct _FM_CTRL  SHADOW_FM_CTRL;

extern struct _WM_CTRL  SHADOW_WM_CTRL;

extern struct _SDRAM_CTRL SHADOW_SDRAM_CTRL;


void REGS_ASSIGN(){

}

#define REGS_ASSIGN( dst_p,src )            \
   memcpy( dst_p , &(src) , sizeof((src)) ); 