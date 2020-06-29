
#include "defs.h"
#include "dma.h"
#include "int_handler.h"
#include "assert.h"


void INT_Disable(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port){
	NVIC_DisableIRQ(IRQ);
	CM3DS_MPS2_gpio_ClrIntEnable(gpio,port);
}

void INT_Clear(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port){
	CM3DS_MPS2_gpio_IntClear(gpio, port);
}

void INT_Enable(IRQn_Type IRQ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port){
	NVIC_ClearPendingIRQ(IRQ);
	NVIC_EnableIRQ(IRQ);
	CM3DS_MPS2_gpio_IntClear(gpio, port);
	CM3DS_MPS2_gpio_SetIntEnable(gpio,port);
}


void dma_next_round( DMAGroupConfig dma_group_config,volatile int* dma_cnt, int sg_num,
	 volatile MODULE_STATE*  state, DMA_ID dma_id , IRQn_Type interrupt ,CM3DS_MPS2_GPIO_TypeDef* gpio,int port ){

		int sg;
    assert( *dma_cnt <= dma_group_config.dma_length && *state == RUNNING);

    if( *dma_cnt < dma_group_config.dma_length){

				dbg_puts("dma_set:\tid:%s,\tcnt:(%d/%d),\n",GET_DMA_NAME(dma_id),*dma_cnt,dma_group_config.dma_length);
        
        //重新配置DMA
			
				//配置dma设置
				dma_config(dma_id,0,sg_num,false);
				
				
				//配置dma sg
				for(sg = 0; sg < sg_num ; sg++){
			
					DMAConfig* dma_config = & (dma_group_config.dma[ (*dma_cnt) + sg ]);
			
					dma_sg_set( dma_id,1, dma_config->rd_addr,dma_config->wr_addr,dma_config->size);
				}
      
        //清空中断
        
				dma_int_clear(dma_id);
				INT_Clear(interrupt,gpio,port);

        //使能DMA
        dma_enable(dma_id);
				
				(*dma_cnt) += sg_num;

    }
    else{
        *dma_cnt = 0; 
        *state = END;
				//禁止中断
				INT_Disable(interrupt,gpio,port);
    }

    return ;
}
	






void int_init(){
	
	//设置output用于软件模拟中断触发
	//CM3DS_MPS2_gpio_SetOutEnable(CM3DS_MPS2_GPIO0, 0xffff); //set output enable to output on ports [31:0] of GPIO 0
		
	CM3DS_MPS2_gpio_SetIntRisingEdge(FM_INT_IO,FM_INT_PORT);
	CM3DS_MPS2_gpio_SetIntRisingEdge(FMDMA_INT_IO,FMDMA_INT_PORT); //set pin  to rising edge interrupts
	CM3DS_MPS2_gpio_SetIntRisingEdge(WMDMA_INT_IO,WMDMA_INT_PORT);
	CM3DS_MPS2_gpio_SetIntRisingEdge(BMDMA_INT_IO,BMDMA_INT_PORT);
	CM3DS_MPS2_gpio_SetIntRisingEdge(BFDMA_INT_IO,BFDMA_INT_PORT);
	CM3DS_MPS2_gpio_SetIntRisingEdge(IFDMA_INT_IO,IFDMA_INT_PORT);
	CM3DS_MPS2_gpio_SetIntRisingEdge(OFDMA_INT_IO,OFDMA_INT_PORT);
	
	
	/*NVIC_ClearPendingIRQ(FM_IRQ);				//clear all global NVIC PORT0 pending interrupts
	NVIC_ClearPendingIRQ(FMDMA_IRQ);
	NVIC_ClearPendingIRQ(WMDMA_IRQ);
	NVIC_ClearPendingIRQ(BMDMA_IRQ);
	NVIC_ClearPendingIRQ(BFDMA_IRQ);
	NVIC_ClearPendingIRQ(WBDMA_IRQ);
	NVIC_ClearPendingIRQ(IFDMA_IRQ);
	NVIC_ClearPendingIRQ(OFDMA_IRQ);
	
	
	NVIC_EnableIRQ(FM_IRQ);
	NVIC_EnableIRQ(FMDMA_IRQ);
	NVIC_EnableIRQ(WMDMA_IRQ);
	NVIC_EnableIRQ(BMDMA_IRQ);
	NVIC_EnableIRQ(BFDMA_IRQ);
	NVIC_EnableIRQ(WBDMA_IRQ);
	NVIC_EnableIRQ(IFDMA_IRQ);
	NVIC_EnableIRQ(OFDMA_IRQ);	*/
	
	/*
	INT_Enable(FM_IRQ,FM_INT_IO,FM_INT_PORT);
	INT_Enable(FMDMA_IRQ,FMDMA_INT_IO,FMDMA_INT_PORT);
	INT_Enable(WMDMA_IRQ,WMDMA_INT_IO,WMDMA_INT_PORT);
	INT_Enable(BMDMA_IRQ,BMDMA_INT_IO,BMDMA_INT_PORT);
	INT_Enable(BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT);
	INT_Enable(WBDMA_IRQ,WBDMA_INT_IO,WBDMA_INT_PORT);
	INT_Enable(IFDMA_IRQ,IFDMA_INT_IO,IFDMA_INT_PORT);
	INT_Enable(OFDMA_IRQ,OFDMA_INT_IO,OFDMA_INT_PORT);
	*/

}



//INT_HANDLER( FM_IRQ ){
void FM_IRQ_HANDLER(){


    assert( 
				(s2chip_status.module_inner_status.fm.config_outer_cnt)
				<= (s2chip_status.layer_config->fm.loop) &&
				(s2chip_status.module_inner_status.fm.config_cnt) 
        <= (s2chip_status.layer_config->fm.config_length) && 
        s2chip_status.module_state.fm == RUNNING
        );

		
    if( s2chip_status.module_inner_status.fm.config_outer_cnt <
        s2chip_status.layer_config->fm.loop
				&& s2chip_status.module_inner_status.fm.config_cnt <
        s2chip_status.layer_config->fm.config_length )
    {
        //重新配置 FM
				dbg_puts("fm_set:\tcnt:(%d/%d,%d/%d),\n",s2chip_status.module_inner_status.fm.config_cnt,s2chip_status.layer_config->fm.config_length,
					s2chip_status.module_inner_status.fm.config_outer_cnt,s2chip_status.layer_config->fm.loop);
        
				FMRoundConfig fm_config = s2chip_status.layer_config->fm.config[ s2chip_status.module_inner_status.fm.config_cnt];
				FM_CTRL->CONFIG_KER_STR_POOL_CHN  = FM_KERNEL(fm_config.kernel)| FM_STRIDE(fm_config.stride)|FM_POOLING(fm_config.pooling) | FM_CHANNEL(fm_config.shape.channel);
				FM_CTRL->CONFIG_ROW_COL = FM_ROW(fm_config.shape.height)| FM_COL(fm_config.shape.width);
				FM_CTRL->CONFIG_PADDING = FM_PADDING_TOP(fm_config.padding.top)|FM_PADDING_BOTTOM(fm_config.padding.bottom)|
							FM_PADDING_LEFT(fm_config.padding.left) | FM_PADDING_RIGHT(fm_config.padding.right);
				
				//配置ROUND READ（目前不使用）
				FM_CTRL->CONFIG_ROUND = FM_ROUND_READ_SIG(0) | FM_ROUND_READ_TIMES(0);	
			
				//->使能FM
				
				
				
				//更新 计数器
        s2chip_status.module_inner_status.fm.config_cnt ++;
				if(s2chip_status.module_inner_status.fm.config_cnt ==
        s2chip_status.layer_config->fm.config_length
				){
					s2chip_status.module_inner_status.fm.config_cnt = 0;
					s2chip_status.module_inner_status.fm.config_outer_cnt ++ ;
				}
			
			
				INT_Clear(FM_IRQ,FM_INT_IO,FM_INT_PORT);
    }
    else{
				//关闭中断
			
				s2chip_status.module_inner_status.fm.config_outer_cnt = 0;
        s2chip_status.module_inner_status.fm.config_cnt = 0;
        s2chip_status.module_state.fm = END;
				
				INT_Disable(FM_IRQ,FM_INT_IO,FM_INT_PORT);
    }
  

}

//INT_HANDLER( FMDMA_IRQ ){
void FMDMA_IRQ_HANDLER(){
		
    assert( s2chip_status.module_state.fm == RUNNING );
  
		//volatile int* dma_outer_cnt = &(s2chip_status.module_inner_status.fmdma.dma_cnt); //外循环，对应loop
	
		volatile int* dma_outer_cnt = &(s2chip_status.module_inner_status.fmdma.dma_outer_cnt);
    volatile int* dma_cnt = &(s2chip_status.module_inner_status.fmdma.dma_cnt);
		volatile int* dma_inner_cnt = &(s2chip_status.module_inner_status.fmdma.dma_inner_cnt);
    FMDMAConfig dma_cfg = s2chip_status.layer_config->fm.config[*dma_cnt].dma;
	
		

	
    if( *dma_outer_cnt <  s2chip_status.layer_config->fm.loop &&
				*dma_cnt < s2chip_status.layer_config->fm.config_length && 
        *dma_inner_cnt < dma_cfg.loop 
        ){
				
				dbg_puts("dma_set:\tid:%s,\tcnt:(%d/%d),\n",GET_DMA_NAME(FMDMA),*dma_cnt,s2chip_status.layer_config->fm.config_length);
					
				int dma_configs_len = MIN( dma_cfg.loop - *dma_inner_cnt,32);
				int fm_end = (dma_configs_len + *dma_inner_cnt)>=dma_cfg.loop;
					
					
				//DMAConfig dma_configs[ dma_configs_len ];
        //重新配置一系列FMDMA
					
				//配置DMA
				dma_config( FMDMA, 0, dma_configs_len, fm_end); 
					
				//配置sg
				for(int i = 0,rd_addr = dma_cfg.rd_addr,wr_addr = dma_cfg.wr_addr;i< dma_configs_len;i++){
					
					
					dma_sg_set(FMDMA,i,rd_addr,wr_addr,dma_cfg.size);
					
					rd_addr += dma_cfg.step;
					wr_addr += dma_cfg.size;
				}
				
				
								
        //使能FMDMA
				
				INT_Clear(FMDMA_IRQ,FMDMA_INT_IO,FMDMA_INT_PORT);
				dma_enable(FMDMA);
					
				//更新计数器
				(*dma_inner_cnt) += dma_configs_len;
				if( *dma_inner_cnt >= dma_cfg.loop){
					
						*dma_inner_cnt = 0;
						(*dma_cnt) ++;
						if( *dma_cnt == s2chip_status.layer_config->fm.config_length)
						{
							(*dma_outer_cnt) ++;
							*dma_cnt = 0;
						}
				}
				
    }
    else{
        //s2chip_status.module_state.fm = END; //更新应该发生在FM结束后
				s2chip_status.module_inner_status.fmdma.dma_outer_cnt = 0;
        s2chip_status.module_inner_status.fmdma.dma_cnt = 0;
        s2chip_status.module_inner_status.fmdma.dma_inner_cnt = 0;
				INT_Disable(FMDMA_IRQ,FMDMA_INT_IO,FMDMA_INT_PORT);
    }


}

//INT_HANDLER( WMDMA_IRQ ){
void WMDMA_IRQ_HANDLER(){

    dma_next_round(s2chip_status.layer_config->wm.dma,
        &(s2chip_status.module_inner_status.wmdma.dma_cnt),1,
        &(s2chip_status.module_state.wm), WMDMA,WMDMA_IRQ,WMDMA_INT_IO,WMDMA_INT_PORT
    );
}

//INT_HANDLER( BFDMA_IRQ){
void BFDMA_IRQ_HANDLER(){

    dma_next_round(s2chip_status.layer_config->ppu.bbqs.bf.dma,
        &(s2chip_status.module_inner_status.bfdma.dma_cnt),1,
        &(s2chip_status.module_state.bf), BFDMA,BFDMA_IRQ,BFDMA_INT_IO,BFDMA_INT_PORT
    );
}

//INT_HANDLER( BMDMA_IRQ){
void BMDMA_IRQ_HANDLER(){

    dma_next_round(s2chip_status.layer_config->ppu.bbqs.bm.dma,
        &(s2chip_status.module_inner_status.bmdma.dma_cnt),1,
        &(s2chip_status.module_state.bm), BMDMA,BMDMA_IRQ , BMDMA_INT_IO, BMDMA_INT_PORT
    );
}


//INT_HANDLER(IFDMA_IRQ){
void IFDMA_IRQ_HANDLER(){

		//dbg_puts_d("ifdma_handler");
	
    assert( s2chip_status.module_state.net_load == RUNNING ||
        s2chip_status.module_state.feature_load == RUNNING
    );
	

    if( s2chip_status.module_state.net_load == RUNNING ){

        dma_next_round(  s2chip_status.io_config->net_load,
            &s2chip_status.module_inner_status.net_load.dma_cnt,1,
            &s2chip_status.module_state.net_load,IFDMA,IFDMA_IRQ , IFDMA_INT_IO,IFDMA_INT_PORT
        );
    }
    else{
        dma_next_round(
            s2chip_status.io_config->feature_load,
            &s2chip_status.module_inner_status.feature_load.dma_cnt,1,
            &s2chip_status.module_state.feature_load,IFDMA,IFDMA_IRQ , IFDMA_INT_IO,IFDMA_INT_PORT
        );
    }
}

//INT_HANDLER(OFDMA_IRQ){
void OFDMA_IRQ_HANDLER(){
        dma_next_round(
            s2chip_status.io_config->feature_store,
            &s2chip_status.module_inner_status.feature_store.dma_cnt,1,
            &s2chip_status.module_state.feature_store,OFDMA,OFDMA_IRQ, OFDMA_INT_IO , OFDMA_INT_PORT
        );
}

//INT_HANDLER(WBDMA_IRQ){
void WBDMA_IRQ_HANDLER(){
    dma_next_round(
        s2chip_status.layer_config->ppu.wb.dma,
        &s2chip_status.module_inner_status.wbdma.dma_cnt,1,
        &s2chip_status.module_state.wb,WBDMA,WBDMA_IRQ , WBDMA_INT_IO, WMDMA_INT_PORT
    );
}
