#include "init.h"
#include "dma.h"

#include "misc.h"
#include "defs.h"
#include "int_handler.h"


extern int feature_load();
extern int pad_set_direction(int);
extern int clk_set(int,int );


int hash_data( int addr){
	return (addr + 0xabc423f1)^0x12345678;
}
int test_sdram(int size){
		printf("sdram write\n");
		for(int i = 0; i< size/4;i=i+1){
				SDRAM->data[i] = hash_data(i);
		}
		printf("sdram read\n");
		for(int i = 0; i< size/4;i=i+1){
				int a = SDRAM->data[i];
				if( a!= hash_data(i)){
						printf("ERROR in sdram\n");
				}else{
						printf("SUCCESS in sdram\n");
				}
		}
}
int test_access( void* addr , int size , char* str){
	
		uint32_t res=0;
		volatile uint32_t * addrr = addr;
	
		printf("%s write 1\n", str);
		for( int i = 0 ; i < size/4 ; i=i+1){
				*(addrr+i) = 1;
		}
		
		printf("%s read \n", str);
		for( int i = 0 ; i < size/4 ; i=i+1){
				res += *(addrr+i);
		}
		
		printf("%s write 0\n", str);
		for( int i = 0 ; i < size/4 ; i=i+1){
				*(addrr+i) = 0;
		}
		printf("%s access success \n", str);
			
}

int min( int a,  int b){
	if( a > b) return b;
	return a;
}

int bus_access_test(){
	 
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	
		/*UartStdOutInit();
		printf("fast uart init\n");
		printf("fast uart init\n");
	*/
	

		UartStdOutInit();
	

		printf(" bus_access_test init\n");
		
		
		test_access( PAD_CTRL , min( sizeof(*PAD_CTRL),100) , "pad");
		pad_init();
		//test_access( CLKGEN_CTRL , min(sizeof(*CLKGEN_CTRL), 100) , "clk");
		
		
		//dma
	
		//sdram
		test_access( SDRAM_CTRL , min(sizeof(*SDRAM_CTRL) , 100), "sdram");
		test_access( FM_CTRL , min(sizeof(*FM_CTRL) , 100) , "fm");
		test_access( WM_CTRL , min(sizeof(*WM_CTRL),100) , "wm" );
		
		test_access( PE_CTRL , min(sizeof(*PE_CTRL),100) , "pe");
		test_access( PPU_CTRL , min(sizeof(*PPU_CTRL), 100) , "ppu");
		test_access( NMS_CTRL , min(sizeof(*NMS_CTRL), 100) , "NMS");
		
		test_access( EXT_INT_OUT_CTRL, min(sizeof(*EXT_INT_OUT_CTRL) , 100) , "int");
		
		test_access( 0x40020000 , 12 , "fpga");
		
		test_sdram( 256);
		
		for(int i = 0 ; i< 9  ;i++)
		{
				dma_config( (DMA_ID)(0x40260000 + i*0x100) , 0 , 0 , 0);
				printf("dma access %i test\n" , i);
		}
		
		printf("-------------- bus_access_test success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


}