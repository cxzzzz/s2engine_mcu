
#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

typedef struct{

	  uint32_t rd_addr;
		uint32_t wr_addr;
    uint32_t size;

}DMAConfig;

typedef struct{

    int dma_length;
    DMAConfig* dma;

}DMAGroupConfig;

typedef struct{

	uint32_t rd_addr;
    uint32_t wr_addr;
    uint32_t size;
    uint32_t step;
    uint32_t loop;

}FMDMAConfig;

typedef struct {

    struct{
        uint8_t fsign;
    }pe;

    struct{
        uint8_t kernel;
        uint8_t stride;
    }ce;

    struct{
        uint8_t en;
    }comp;

}PEConfig; //CE PE


typedef struct{

    uint32_t loop;
    DMAGroupConfig dma;

}WMConfig;


typedef struct{ 

    FMDMAConfig dma;


    uint32_t kernel;
    uint32_t stride;
    uint32_t pooling;

    struct{
        uint32_t height;
        uint32_t width;
        uint32_t channel;
    }shape;

    struct{
        uint32_t top;
        uint32_t bottom;
        uint32_t left;
        uint32_t right;
    }padding;

    uint32_t round_read_times;
    uint8_t  round_read_sig;

} FMRoundConfig;


//typedef struct{
//    uint32_t dma_length; 
//    FMDMAConfig* dma;
//}FMDMAGroupConfig;
//
//typedef FMDMAGroupConfig FMConfig;

typedef struct{
	
		uint32_t loop;
	
    uint32_t config_length; 

    FMRoundConfig* config;

}FMConfig;

typedef struct{

    struct{
        uint8_t sc_sign;
        uint8_t sc_en;
				uint32_t loop;

        struct {
            DMAGroupConfig dma;
        }bf;

        struct{
            uint32_t loop;
            DMAGroupConfig dma;
        }bm;

    }bbqs;

    struct{
        uint8_t en;
    }act;

    struct{
        uint8_t en;
        uint8_t sign;
        uint8_t kernel;
    }pool;

    struct{
        uint32_t size;
        uint32_t step;
    }dc;



    struct{
        DMAGroupConfig dma;
    }wb;

}PPUConfig;

typedef struct{

    PEConfig pe;
    WMConfig wm;
    FMConfig fm;
    PPUConfig ppu;

}LayerConfig;

typedef struct{
    uint32_t layer_length;
    LayerConfig* layer;

}NetConfig;

typedef struct{

    DMAGroupConfig net_load,feature_load,feature_store;

}IOConfig;

#endif
