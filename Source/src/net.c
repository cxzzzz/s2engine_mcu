#include "defs.h"


        
DMAConfig conv1_wm_dma_dma[] = 
            { {  rd_addr : 327680,
        wr_addr : 0,
        size : 4608,
         } , };
    
        
FMRoundConfig conv1_fm_config[] = 
            { {  shape : {  height : 34,
        width : 20,
        channel : 1,
         },
        kernel : 3,
        stride : 1,
        pooling : 2,
        padding : {  top : 1,
        bottom : 1,
        left : 1,
        right : 0,
         },
        round_read_times : 0,
        round_read_sig : 0,
        dma : {  wr_addr : 0,
        rd_addr : 0,
        size : 9728,
        step : 16384,
        loop : 1,
         },
         } ,{  shape : {  height : 34,
        width : 16,
        channel : 1,
         },
        kernel : 3,
        stride : 1,
        pooling : 2,
        padding : {  top : 1,
        bottom : 1,
        left : 0,
        right : 1,
         },
        round_read_times : 0,
        round_read_sig : 0,
        dma : {  wr_addr : 0,
        rd_addr : 8704,
        size : 7680,
        step : 16384,
        loop : 1,
         },
         } , };
    
        
DMAConfig conv1_ppu_bbqs_bf_dma_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 0,
        size : 16384,
         } , };
    
        
DMAConfig conv1_ppu_bbqs_bm_dma_dma[] = 
            { {  rd_addr : 655360,
        wr_addr : 0,
        size : 128,
         } , };
    
        
DMAConfig conv1_ppu_wb_dma_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 16384,
        size : 4096,
         } , };
    
        
LayerConfig net_layer[] = 
            { {  pe : {  pe : {  fsign : True,
         },
        ce : {  kernel : 3,
        stride : 1,
         },
        comp : {  en : False,
         },
         },
        wm : {  loop : 64,
        dma : {  dma_length : 1,
        dma : conv1_wm_dma_dma,
         },
         },
        fm : {  loop : 1,
        config_length : 2,
        config : conv1_fm_config,
         },
        ppu : {  bbqs : {  sc_sign : True,
        sc_en : True,
        loop : 1024,
        bf : {  dma : {  dma_length : 1,
        dma : conv1_ppu_bbqs_bf_dma_dma,
         },
         },
        bm : {  loop : 1024,
        dma : {  dma_length : 1,
        dma : conv1_ppu_bbqs_bm_dma_dma,
         },
         },
        dp : {  size : 1,
        step : 1,
         },
        cv : {  sc_width : 0,
        out_width : 0,
        sc_shift : 1,
         },
         },
        act : {  en : True,
         },
        pool : {  en : True,
        sign : False,
        kernel : 0,
         },
        dc : {  size : 16,
        step : 16,
         },
        wb : {  dma : {  dma_length : 1,
        dma : conv1_ppu_wb_dma_dma,
         },
         },
         },
         } , };
    
        
NetConfig net = 
            {  layer_length : 1,
        layer : net_layer,
         };
    
        
DMAConfig net_params_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 327680,
        size : 4608,
         } ,{  rd_addr : 0,
        wr_addr : 655360,
        size : 128,
         } , };
    
        
DMAConfig net_input_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 0,
        size : 16384,
         } , };
    
        
DMAConfig net_output_dma[] = 
            { {  rd_addr : 16384,
        wr_addr : 0,
        size : 4096,
         } , };
    
        
IOConfig net_io = 
            {  net_load : {  dma_length : 2,
        dma : net_params_dma,
         },
        feature_load : {  dma_length : 1,
        dma : net_input_dma,
         },
        feature_store : {  dma_length : 1,
        dma : net_output_dma,
         },
         };
    