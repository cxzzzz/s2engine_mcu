













#include "defs.h"


        
DMAConfig conv1_wm_dma_dma[] = 
            { {  rd_addr : 327680,
        wr_addr : 0,
        size : 18432,
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
    
        
DMAConfig conv1_ppu_bbqs_bm_dma_dma[] = 
            { {  rd_addr : 655360,
        wr_addr : 0,
        size : 512,
         } , };
    
        
DMAConfig conv1_ppu_wb_dma_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 16384,
        size : 16384,
         } , };
    
        
DMAConfig conv2_wm_dma_dma[] = 
            { {  rd_addr : 346112,
        wr_addr : 0,
        size : 73728,
         } , };
    
        
FMRoundConfig conv2_fm_config[] = 
            { {  shape : {  height : 18,
        width : 8,
        channel : 4,
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
        rd_addr : 16384,
        size : 1792,
        step : 4096,
        loop : 4,
         },
         } ,{  shape : {  height : 18,
        width : 8,
        channel : 4,
         },
        kernel : 3,
        stride : 1,
        pooling : 2,
        padding : {  top : 1,
        bottom : 1,
        left : 0,
        right : 0,
         },
        round_read_times : 0,
        round_read_sig : 0,
        dma : {  wr_addr : 0,
        rd_addr : 17664,
        size : 2048,
        step : 4096,
        loop : 4,
         },
         } ,{  shape : {  height : 18,
        width : 6,
        channel : 4,
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
        rd_addr : 19200,
        size : 1280,
        step : 4096,
        loop : 4,
         },
         } , };
    
        
DMAConfig conv2_ppu_bbqs_bm_dma_dma[] = 
            { {  rd_addr : 655872,
        wr_addr : 0,
        size : 512,
         } , };
    
        
DMAConfig conv2_ppu_wb_dma_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 0,
        size : 4096,
         } , };
    
        
DMAConfig conv3_wm_dma_dma[] = 
            { {  rd_addr : 419840,
        wr_addr : 0,
        size : 147456,
         } , };
    
        
FMRoundConfig conv3_fm_config[] = 
            { {  shape : {  height : 10,
        width : 10,
        channel : 4,
         },
        kernel : 3,
        stride : 1,
        pooling : 1,
        padding : {  top : 1,
        bottom : 1,
        left : 1,
        right : 1,
         },
        round_read_times : 0,
        round_read_sig : 0,
        dma : {  wr_addr : 0,
        rd_addr : 0,
        size : 1024,
        step : 1024,
        loop : 4,
         },
         } , };
    
        
DMAConfig conv3_ppu_bbqs_bm_dma_dma[] = 
            { {  rd_addr : 656384,
        wr_addr : 0,
        size : 1024,
         } , };
    
        
DMAConfig conv3_ppu_wb_dma_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 4096,
        size : 8192,
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
        fm : {  loop : 4,
        config_length : 2,
        config : conv1_fm_config,
         },
        ppu : {  bbqs : {  sc_sign : True,
        sc_en : False,
        loop : 1024,
        bf : {  dma : {  dma_length : 0,
        dma : NULL,
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
         } ,{  pe : {  pe : {  fsign : False,
         },
        ce : {  kernel : 3,
        stride : 1,
         },
        comp : {  en : False,
         },
         },
        wm : {  loop : 16,
        dma : {  dma_length : 1,
        dma : conv2_wm_dma_dma,
         },
         },
        fm : {  loop : 4,
        config_length : 3,
        config : conv2_fm_config,
         },
        ppu : {  bbqs : {  sc_sign : True,
        sc_en : False,
        loop : 256,
        bf : {  dma : {  dma_length : 0,
        dma : NULL,
         },
         },
        bm : {  loop : 256,
        dma : {  dma_length : 1,
        dma : conv2_ppu_bbqs_bm_dma_dma,
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
        dc : {  size : 8,
        step : 8,
         },
        wb : {  dma : {  dma_length : 1,
        dma : conv2_ppu_wb_dma_dma,
         },
         },
         },
         } ,{  pe : {  pe : {  fsign : False,
         },
        ce : {  kernel : 3,
        stride : 1,
         },
        comp : {  en : False,
         },
         },
        wm : {  loop : 8,
        dma : {  dma_length : 1,
        dma : conv3_wm_dma_dma,
         },
         },
        fm : {  loop : 8,
        config_length : 1,
        config : conv3_fm_config,
         },
        ppu : {  bbqs : {  sc_sign : True,
        sc_en : False,
        loop : 128,
        bf : {  dma : {  dma_length : 0,
        dma : NULL,
         },
         },
        bm : {  loop : 128,
        dma : {  dma_length : 1,
        dma : conv3_ppu_bbqs_bm_dma_dma,
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
        pool : {  en : False,
        sign : False,
        kernel : 0,
         },
        dc : {  size : 8,
        step : 16,
         },
        wb : {  dma : {  dma_length : 1,
        dma : conv3_ppu_wb_dma_dma,
         },
         },
         },
         } , };
    
        
NetConfig net = 
            {  layer_length : 3,
        layer : net_layer,
         };
    
        
DMAConfig net_params_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 327680,
        size : 18432,
         } ,{  rd_addr : 0,
        wr_addr : 346112,
        size : 73728,
         } ,{  rd_addr : 0,
        wr_addr : 419840,
        size : 147456,
         } ,{  rd_addr : 0,
        wr_addr : 655360,
        size : 512,
         } ,{  rd_addr : 0,
        wr_addr : 655872,
        size : 512,
         } ,{  rd_addr : 0,
        wr_addr : 656384,
        size : 1024,
         } , };
    
        
DMAConfig net_input_dma[] = 
            { {  rd_addr : 0,
        wr_addr : 0,
        size : 16384,
         } , };
    
        
DMAConfig net_output_dma[] = 
            { {  rd_addr : 4096,
        wr_addr : 0,
        size : 8192,
         } , };
    
        
IOConfig net_io = 
            {  net_load : {  dma_length : 6,
        dma : net_params_dma,
         },
        feature_load : {  dma_length : 1,
        dma : net_input_dma,
         },
        feature_store : {  dma_length : 1,
        dma : net_output_dma,
         },
         };
    