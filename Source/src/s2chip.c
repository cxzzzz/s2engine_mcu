



#include <stdio.h>
#include <stdint.h>
#include <string.h>


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






void feature_load(){
    s2chip_status.module_state.feature_load = RUNNING;
		s2chip_status.module_inner_status.feature_load.dma_cnt = 0;

    INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);

    //CALL_INT_HANDLER(IFDMA_IRQ);
		IFDMA_IRQ_HANDLER();

    WAIT( s2chip_status.module_state.feature_load == END);

    INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
}

void feature_store(){
    s2chip_status.module_state.feature_store = RUNNING;
		s2chip_status.module_inner_status.feature_store.dma_cnt = 0;

    //int_enable(OFDMA_IRQ);
	
		INT_Enable(OFDMA_IRQ,OFDMA_INT_IO,OFDMA_INT_PORT);

    //CALL_INT_HANDLER(OFDMA_IRQ);
		OFDMA_IRQ_HANDLER();

    WAIT( s2chip_status.module_state.feature_store == END);

    INT_Disable(OFDMA_IRQ,OFDMA_INT_IO,OFDMA_INT_PORT);
}

void layer_init(int layer){
    s2chip_status.layer_id = layer; 
    s2chip_status.layer_config = &(s2chip_status.net_config->layer[layer]);
    memset((void*)&(s2chip_status.module_inner_status),0,sizeof(s2chip_status.module_inner_status));


		//->复位各模块（暂时没有复位的地址）
		  //必须对PPU->BBQS_LOOP进行复位
		RESET(CLKGEN_CTRL->RST.BBQS);
		
    //初始化wm ppu参数
	
			//WM

		dbg_puts_d("wm config");
		WM_CTRL->LOOP = WM_LOOP(s2chip_status.layer_config->wm.loop);
		
		dbg_puts_d("pe config");
			//PE
		PEConfig pe_config = s2chip_status.layer_config->pe;
		PE_CTRL->CE = PE_CE_KERNEL( pe_config.ce.kernel) | PE_CE_STRIDE(pe_config.ce.stride);
		PE_CTRL->COMPRESS = PE_COMPRESS_EN(pe_config.comp.en);
		PE_CTRL->PE = PE_PE_FSIGN(pe_config.pe.fsign);
			
			//PPU
		
		dbg_puts_d("ppu config");
		PPUConfig ppu_config = s2chip_status.layer_config->ppu;
		PPU_CTRL->ACT = PPU_ACT_EN(ppu_config.act.en);
    //load数据以前需要将loop设为0，避免初始化后就load数据产生错误
		PPU_CTRL->BBQS = PPU_BBQS_SYS_EN|PPU_BBQS_SYS_LOOP(0) | PPU_BBQS_SYS_SC_EN(ppu_config.bbqs.sc_en) | PPU_BBQS_SYS_SC_SIGN(ppu_config.bbqs.sc_sign);
    PPU_CTRL->BBQS_DP = PPU_BBQS_DP_SIZE(ppu_config.bbqs.dp.size) | PPU_BBQS_DP_STEP(ppu_config.bbqs.dp.step);
		PPU_CTRL->BBQS_CV = PPU_BBQS_CV_OUT_WIDTH(ppu_config.bbqs.cv.out_width) | PPU_BBQS_CV_SC_SHIFT( ppu_config.bbqs.cv.sc_shift ) | PPU_BBQS_CV_SC_WIDTH( ppu_config.bbqs.cv.sc_width);
		PPU_CTRL->DC = PPU_DC_SIZE(ppu_config.dc.size) | PPU_DC_STEP(ppu_config.dc.step);
		PPU_CTRL->POOL = PPU_POOL_EN(ppu_config.pool.en) | PPU_POOL_KERNEL(ppu_config.pool.kernel) | PPU_POOL_SIGN(ppu_config.pool.sign);
			
			//初始化FM的配置信息
		dbg_puts_d("fm config");
		INT_Enable( FM_IRQ,FM_INT_IO,FM_INT_PORT);
		s2chip_status.module_state.fm = RUNNING;
    //CALL_INT_HANDLER(FM_IRQ);
		FM_IRQ_HANDLER();

    //初始化bm
		dbg_puts_d("bm loadding");
    INT_Enable( BMDMA_IRQ,BMDMA_INT_IO,BMDMA_INT_PORT);
    s2chip_status.module_state.bm = RUNNING;
    //CALL_INT_HANDLER(BFDMA_IRQ);
		BMDMA_IRQ_HANDLER();
    WAIT( s2chip_status.module_state.bm == END);
		dbg_puts_d("bm loaded");
    //INT_Disable(BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
		PPU_CTRL->BBQS = PPU_BBQS_SYS_EN |PPU_BBQS_SYS_LOOP(ppu_config.bbqs.loop) | PPU_BBQS_SYS_SC_EN(ppu_config.bbqs.sc_en) | PPU_BBQS_SYS_SC_SIGN(ppu_config.bbqs.sc_sign);
}

void layer_run(int layer){ //主要使能各个dma

    assert( layer < s2chip_status.net_config->layer_length);

    layer_init(layer);
	
		dbg_puts_d( "layer %d init",layer );

    //初始化fmdma wmdma bfdma wbdma
    s2chip_status.module_state.fm = RUNNING;
    s2chip_status.module_state.wm = RUNNING;
		s2chip_status.module_state.bf = RUNNING;
    s2chip_status.module_state.wb = RUNNING;
		
    //int_enable( FMDMA_IRQ);
    //CALL_INT_HANDLER(FMDMA_IRQ);
		INT_Enable(FMDMA_IRQ,FMDMA_INT_IO,FMDMA_INT_PORT);
		FMDMA_IRQ_HANDLER();
    //int_enable( WMDMA_IRQ);
    //CALL_INT_HANDLER(WMDMA_IRQ);
		INT_Enable(WMDMA_IRQ,WMDMA_INT_IO,WMDMA_INT_PORT);
		WMDMA_IRQ_HANDLER();
    
		//CALL_INT_HANDLER(BFDMA_IRQ);
		INT_Enable(BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
		BFDMA_IRQ_HANDLER();
		
    //int_enable( WBDMA_IRQ);
    //CALL_INT_HANDLER(WBDMA_IRQ);
		INT_Enable(WBDMA_IRQ,WBDMA_INT_IO,WBDMA_INT_PORT);
		WBDMA_IRQ_HANDLER();
	
		

    WAIT( s2chip_status.module_state.fm == END &&
        s2chip_status.module_state.wm == END &&
        s2chip_status.module_state.bf == END &&
        s2chip_status.module_state.wb == END
    );

    return;
}

void pad_set_direction(int input){
	 PAD_CTRL->ioen.ie1 = is_true(input);
	 PAD_CTRL->ioen.oen1 = is_true(input);
}

int _main_s2chip(){
	
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	
	
		UartStdOutInit();
		dbg_puts_d("uart init");

    s2chip_init();
	dbg_puts_d("s2chip init");
	
	

    net_init();
		dbg_puts_d("net init");

	
    while(true){
				pad_set_direction(1);
        
        feature_load();
				dbg_puts_d("feature loaded");
			
				
        for(int layer = 0; layer < s2chip_status.net_config->layer_length;layer ++){
						printf(">>>>>>>>>>> layer %d start <<<<<<<<<<<\n",layer);
            layer_run(layer);
						//dbg_puts_d("layer %d done",layer);
						printf(">>>>>>>>>>> layer %d done <<<<<<<<<<<\n",layer);
        }
				
				pad_set_direction(0);
				
        feature_store();
				dbg_puts_d("feature stored");		
				
				printf(">>>>>>>>>> output done >>>>>>>>>>>>>>>>>>>>");
    }
}
