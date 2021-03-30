#include "init.h"
#include "dma.h"
#include "misc.h"

#define HW32_REG(ADDRESS)  (*((volatile unsigned long  *)(ADDRESS)))
#define HW16_REG(ADDRESS)  (*((volatile unsigned short *)(ADDRESS)))
#define HW8_REG(ADDRESS)   (*((volatile unsigned char  *)(ADDRESS)))
	
int write_read_test(int addr,int value){
	/*
	printf("->0000\n");
	int v = HW32_REG(addr);
	*/
	int v;
	
	v = HW32_REG(addr);
	
	printf("->0001\n");
	HW32_REG(addr) = value;
	printf("->0002\n");
	v = HW32_REG(addr);
	printf("->0003\n");
	if( v == value){
		printf("read pass:%x\n",addr);
	}else{
		printf("read error:%x\tin:%x\tout:%x\n",addr,value,v);
	}
	printf("->0004\n");
}




extern int feature_load();
extern int pad_set_direction(int);
extern int clk_set(int,int );
int fpga_reg_test(){
	 
    clock_init();
    pad_init();
	
	/*
		PAD_CTRL->ioen.ie1 = 1;
		PAD_CTRL->ioen.oen1 = 1;
	*/
		pad_set_direction(1);
	
	
		UartStdOutInit();
		printf("fast uart init\n");
		printf("fast uart init\n");
	

		//uart_init(75.0, 38400);

		printf("slow uart init0\n");
		printf("slow uart init1\n");

		printf("slow uart init2\n");
		printf("slow uart init3\n");

	/*
		UartStdOutInit();
		printf("fast uart init\n");
		printf("fast uart init\n");
	*/

	
		/*
			//提高部分区域频率

		//该配置尽量提高 dma频率以提高数据供应速度，同时降低mac频率以提高加速比
		CLKGEN_CTRL->DIVIDE.N1 = 8; //core分频
		CLKGEN_CTRL->DIVIDE.N2 = 9;//dma分频
		CLKGEN_CTRL->DIVIDE.N3 = 30;//mac/ppu分频
		*/


		
		//clk_set(0,0);
		//printf("clk init\n");
		int iiii=0;
		
		int start_addr = 0x44000000;
		
		for(int i = start_addr;i < start_addr+64;i+=4){
				HW32_REG(i) = 0;
		}
		
		for(int i = start_addr;i < start_addr+64;i+=4){
				write_read_test(i,i+0xf1234567);
		}
		
		int xor_key = 0xf1c32a1e;
		for(int i = start_addr; i < start_addr + 1024*1024*1 ; i+=4){
				HW32_REG(i) = i ^ xor_key;
		}
		printf("write 32 success \n");
		for(int i = start_addr; i < start_addr + 1024*1024*1 ; i+=4){
				int value = HW32_REG(i);
				if( value != (i ^xor_key)){
					printf("error in : %x : std:%x : real:%x\n",i,i^xor_key,value);
				}
		}
		printf("read 32 success \n");
		
		xor_key = ~xor_key;
		for(int i = start_addr; i < start_addr + 1024*1024*1 ; i+=1){
				HW8_REG(i) = i ^ xor_key;
		}
		printf("write 8 success \n");

		for(int i = start_addr; i < start_addr + 1024*1024*1 ; i+=1){
				char value = HW8_REG(i);
				if( value != (char)(i ^xor_key) ){
					printf("error in : %x : std:%x : real:%x\n",i,i^xor_key,value);
				}
		}
		printf("read 8 success \n");
		
		while(1);
}