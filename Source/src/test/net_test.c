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


int net_test(){

    clock_init();
    pad_init();
				//配置PAD
		//需要把ie/oen拉高,以把数据改为写模式
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	
	UartStdOutInit();
	dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");

		//INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
	
		//printf("hello");

    //搬运数
    //CALL_INT_HANDLER(IFDMA_IRQ);
		dbg_puts_d("ifdma start");
		s2chip_status.module_state.net_load = RUNNING;
		IFDMA_IRQ_HANDLER();
		dma_wait(IFDMA);
		s2chip_status.module_state.net_load = END;
		dbg_puts_d("ifdma stopped");
		
		dbg_puts_d("weight loaded");
		dbg_puts_d("ifdma start");
		s2chip_status.module_state.net_load = RUNNING;
		IFDMA_IRQ_HANDLER();
		dma_wait(IFDMA);
		s2chip_status.module_state.net_load = END;
		dbg_puts_d("ifdma stopped");
		dbg_puts_d("bbqs loaded");
		
		dbg_puts_d("ifdma start")
		s2chip_status.module_state.feature_load = RUNNING;

    INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
		dma_wait(IFDMA);
		s2chip_status.module_state.feature_load = END;
		dbg_puts_d("ifdma stopped");
	
		dbg_puts_d("feature loaded");


    //等待数据搬运完成
   
	
		int layer = 0;
		//配置各个寄存器
    s2chip_status.layer_id = layer; 
    s2chip_status.layer_config = &(s2chip_status.net_config->layer[layer]);
    memset((void*)&(s2chip_status.module_inner_status),0,sizeof(s2chip_status.module_inner_status));


		//->复位各模块（暂时没有复位的地址）
		  //必须对PPU->BBQS_LOOP进行复位
		RESET(CLKGEN_CTRL->RST.BBQS);
		
    //初始化wm ppu参数
	

			//PE
		dbg_puts_d("pe config");
		PEConfig pe_config = s2chip_status.layer_config->pe;
		PE_CTRL->CE = PE_CE_KERNEL( pe_config.ce.kernel) | PE_CE_STRIDE(pe_config.ce.stride);
		PE_CTRL->COMPRESS = PE_COMPRESS_EN(pe_config.comp.en);
		PE_CTRL->PE = PE_PE_FSIGN(pe_config.pe.fsign);
			
			//PPU
		dbg_puts_d("ppu config");
		PPUConfig ppu_config = s2chip_status.layer_config->ppu;
		PPU_CTRL->ACT = PPU_ACT_EN(ppu_config.act.en);
    //load数据以前需要将loop设为0，避免初始化后就load数据产生错误
		PPU_CTRL->BBQS = PPU_BBQS_SYS_LOOP(0) | PPU_BBQS_SYS_SC_EN(ppu_config.bbqs.sc_en) | PPU_BBQS_SYS_SC_SIGN(ppu_config.bbqs.sc_sign);
    PPU_CTRL->BBQS_DP = PPU_BBQS_DP_SIZE(ppu_config.bbqs.dp.size) | PPU_BBQS_DP_STEP(ppu_config.bbqs.dp.step);
		PPU_CTRL->BBQS_CV = PPU_BBQS_CV_OUT_WIDTH(ppu_config.bbqs.cv.out_width) | PPU_BBQS_CV_SC_SHIFT( ppu_config.bbqs.cv.sc_shift ) | PPU_BBQS_CV_SC_WIDTH( ppu_config.bbqs.cv.sc_width);
		PPU_CTRL->DC = PPU_DC_SIZE(ppu_config.dc.size) | PPU_DC_STEP(ppu_config.dc.step);
		PPU_CTRL->POOL = PPU_POOL_EN(ppu_config.pool.en) | PPU_POOL_KERNEL(ppu_config.pool.kernel) | PPU_POOL_SIGN(ppu_config.pool.sign);
			
			//初始化FM的配置信息
					dbg_puts_d("fm config");
		//INT_Enable( FM_IRQ,FM_INT_IO,FM_INT_PORT);
		s2chip_status.module_state.fm = RUNNING;
    //CALL_INT_HANDLER(FM_IRQ);
		FM_IRQ_HANDLER();

    //初始化bm
		dbg_puts_d("bm config");
    //INT_Enable( BMDMA_IRQ,BMDMA_INT_IO,BMDMA_INT_PORT);
    s2chip_status.module_state.bm = RUNNING;
    //CALL_INT_HANDLER(BFDMA_IRQ);
		
		
		
		//启动bm dma

		BMDMA_IRQ_HANDLER();
	  dbg_puts_d("bm dma started");
		dma_wait(BMDMA);
		s2chip_status.module_state.bm = END;
		  dbg_puts_d("bm dma stopped");
    //WAIT( s2chip_status.module_state.bm == END);
    //INT_Disable(BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
		PPU_CTRL->BBQS = PPU_BBQS_SYS_LOOP(ppu_config.bbqs.loop) | PPU_BBQS_SYS_SC_EN(ppu_config.bbqs.sc_en) | PPU_BBQS_SYS_SC_SIGN(ppu_config.bbqs.sc_sign);
		
					//WM
	
		dbg_puts_d("wm config");
		WM_CTRL->LOOP = WM_LOOP(s2chip_status.layer_config->wm.loop);

		
		
		
		//初始化wm dma
		
		
		//初始化fm dma
		s2chip_status.module_state.wm = RUNNING;
		WMDMA_IRQ_HANDLER();
		 dbg_puts_d("wm dma started");
		
		s2chip_status.module_state.fm = RUNNING;
		FMDMA_IRQ_HANDLER();
				 dbg_puts_d("fm dma started");
		
		

		
		dma_wait(FMDMA);
		dbg_puts_d("fm dma started");
		dma_wait(WMDMA);
		dbg_puts_d("wm dma stopped");

		//目前最多只能运行到这了，理论上能计算出一小小点结果
	
		return 0;
}
