


#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "CM3DS_MPS2.h"

#include "uart_stdout.h"
#include "CM3DS_MPS2_driver.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "defs.h"
#include "int_handler.h"

#include "net.h"

void s2chip_init(){
	s2chip_status.net_config = &net_config;
	s2chip_status.io_config = &io_config;
	int_init();
}

// 将Net数据Load到片上
void net_init(){
    s2chip_status.module_state.net_load = RUNNING;
    //使能IFIFO中断
    
	
		INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
	
		//printf("hello");

    //搬运数
    //CALL_INT_HANDLER(IFDMA_IRQ);
		IFDMA_IRQ_HANDLER();

    //等待数据搬运完成
    WAIT( s2chip_status.module_state.net_load == END);

    //关闭IFIFO中断
    INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
}

void feature_load(){
    s2chip_status.module_state.feature_load = RUNNING;

    INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);

    //CALL_INT_HANDLER(IFDMA_IRQ);
		IFDMA_IRQ_HANDLER();

    WAIT( s2chip_status.module_state.feature_load == END);

    INT_Disable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
}

void feature_store(){
    s2chip_status.module_state.feature_store = RUNNING;

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
		
		
    //初始化wm ppu参数
	
			//WM
		WM_CTRL->LOOP = WM_LOOP(s2chip_status.layer_config->wm.loop);
		
			//PE
		PEConfig pe_config = s2chip_status.layer_config->pe;
		PE_CTRL->CE = PE_CE_KERNEL( pe_config.ce.kernel) | PE_CE_STRIDE(pe_config.ce.stride);
		PE_CTRL->COMPRESS = PE_COMPRESS_EN(pe_config.comp.en);
		PE_CTRL->PE = PE_PE_FSIGN(pe_config.pe.fsign);
			
			//PPU
		
		PPUConfig ppu_config = s2chip_status.layer_config->ppu;
		PPU_CTRL->ACT = PPU_ACT_EN(ppu_config.act.en);
		PPU_CTRL->BBQS = PPU_BBQS_SYS_LOOP(ppu_config.bbqs.loop) | PPU_BBQS_SYS_SC_EN(ppu_config.bbqs.sc_en) | PPU_BBQS_SYS_SC_SIGN(ppu_config.bbqs.sc_sign);
		PPU_CTRL->DC = PPU_DC_SIZE(ppu_config.dc.size) | PPU_DC_STEP(ppu_config.dc.step);
		PPU_CTRL->POOL = PPU_POOL_EN(ppu_config.pool.en) | PPU_POOL_KERNEL(ppu_config.pool.kernel) | PPU_POOL_SIGN(ppu_config.pool.sign);
			
			//FM
		INT_Enable( FM_IRQ,FM_INT_IO,FM_INT_PORT);
		s2chip_status.module_state.fm = RUNNING;
    //CALL_INT_HANDLER(FM_IRQ);
		FM_IRQ_HANDLER();

    //初始化bm
    INT_Enable( BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
    s2chip_status.module_state.bf = RUNNING;
    //CALL_INT_HANDLER(BFDMA_IRQ);
		BFDMA_IRQ_HANDLER();
    WAIT( s2chip_status.module_state.bf == END);
    //INT_Disable(BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
}

void layer_run(int layer){ //主要使能各个dma

    assert( layer < s2chip_status.net_config->layer_length);

    layer_init(layer);

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

int main(){

    s2chip_init();
    net_init();

    while(true){
        
        feature_load();

        for(int layer = 0; layer < s2chip_status.net_config->layer_length;layer ++){
            layer_run(layer);
        }

        feature_store();
    }
}