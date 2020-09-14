#include "CM3DS_MPS2.h"

#include <stdio.h>
#include "uart_stdout.h"
//#include "CM3DS_function.h"

#include "defs.h"


/* Global variables */
volatile int hardfault_occurred;
volatile int hardfault_expected;
volatile int temp_data;

#define HW32_REG(ADDRESS)  (*((volatile unsigned long  *)(ADDRESS)))
#define HW16_REG(ADDRESS)  (*((volatile unsigned short *)(ADDRESS)))
#define HW8_REG(ADDRESS)   (*((volatile unsigned char  *)(ADDRESS)))

int reg_test(void)
{
  int err_code = 0;

  // UART init
  UartStdOutInit();
	
  printf ("\n** START TEST **\n");


//PAD
HW32_REG(PAD_BASE_ADDR + 0x50) = 0x01 ;//UART_IN_MODE
HW32_REG(PAD_BASE_ADDR + 0x58) = 0x01 ;//DATA_OUT_MODE
HW32_REG(PAD_BASE_ADDR + 0x5c) = 0x01 ;//DEBUG_MODE

temp_data = HW32_REG(PAD_BASE_ADDR + 0x50);//UART_IN_MODE
temp_data = HW32_REG(PAD_BASE_ADDR + 0x58);//DATA_OUT_MODE
temp_data = HW32_REG(PAD_BASE_ADDR + 0x5c);//DEBUG_MODE


//CLK passed
HW32_REG(CLKGEN_BASE_ADDR + 0x00) = 0x0f ;//N
HW32_REG(CLKGEN_BASE_ADDR + 0x04) = 0xff ;//M
HW32_REG(CLKGEN_BASE_ADDR + 0x08) = 0x01 ;//Pll_bypass
HW32_REG(CLKGEN_BASE_ADDR + 0x0c) = 0x01 ;//OD
HW32_REG(CLKGEN_BASE_ADDR + 0x10) = 0x02 ;//Sel_Clk_ahb
HW32_REG(CLKGEN_BASE_ADDR + 0x14) = 0x02 ;//Sel_Clk_fm
HW32_REG(CLKGEN_BASE_ADDR + 0x18) = 0x02 ;//Sel_Clk_wm
HW32_REG(CLKGEN_BASE_ADDR + 0x1c) = 0x02 ;//Sel_Clk_bbqs
HW32_REG(CLKGEN_BASE_ADDR + 0x20) = 0x02 ;//Sel_Clk_act
HW32_REG(CLKGEN_BASE_ADDR + 0x24) = 0x02 ;//Sel_Clk_pooling
HW32_REG(CLKGEN_BASE_ADDR + 0x28) = 0x02 ;//Sel_Clk_dc
HW32_REG(CLKGEN_BASE_ADDR + 0x2c) = 0x02 ;//Sel_Clk_compress
HW32_REG(CLKGEN_BASE_ADDR + 0x30) = 0x02 ;//Sel_Clk_pe
HW32_REG(CLKGEN_BASE_ADDR + 0x34) = 0x02 ;//Sel_Clk_ce
HW32_REG(CLKGEN_BASE_ADDR + 0x38) = 0x02 ;//Sel_clk_alignment
HW32_REG(CLKGEN_BASE_ADDR + 0x3c) = 0x02 ;//Sel_Clk_sdram
HW32_REG(CLKGEN_BASE_ADDR + 0x40) = 0x02 ;//Sel_Clk_DMA
HW32_REG(CLKGEN_BASE_ADDR + 0x44) = 0x02 ;//Sel_Clk_fifo
HW32_REG(CLKGEN_BASE_ADDR + 0x48) = 0x02 ;//Sel_Clk_dbgctl
HW32_REG(CLKGEN_BASE_ADDR + 0x4c) = 0x0f ;//Divide_N1
HW32_REG(CLKGEN_BASE_ADDR + 0x50) = 0x0f ;//Divide_N2
HW32_REG(CLKGEN_BASE_ADDR + 0x54) = 0x0f ;//Divide_N3
HW32_REG(CLKGEN_BASE_ADDR + 0x58) = 0x0f ;//Divide_N4
HW32_REG(CLKGEN_BASE_ADDR + 0x5c) = 0x01 ;//Reg_rst_ahb
HW32_REG(CLKGEN_BASE_ADDR + 0x60) = 0x01 ;//Reg_rst_fm
HW32_REG(CLKGEN_BASE_ADDR + 0x64) = 0x01 ;//Reg_rst_wm
HW32_REG(CLKGEN_BASE_ADDR + 0x68) = 0x01 ;//Reg_rst_bbqs
HW32_REG(CLKGEN_BASE_ADDR + 0x6c) = 0x01 ;//Reg_rst_act
HW32_REG(CLKGEN_BASE_ADDR + 0x70) = 0x01 ;//Reg_rst_pooling
HW32_REG(CLKGEN_BASE_ADDR + 0x74) = 0x01 ;//Reg_rst_dc
HW32_REG(CLKGEN_BASE_ADDR + 0x78) = 0x01 ;//Reg_rst_compress
HW32_REG(CLKGEN_BASE_ADDR + 0x7c) = 0x01 ;//Reg_rst_pe
HW32_REG(CLKGEN_BASE_ADDR + 0x80) = 0x01 ;//Reg_rst_ce
HW32_REG(CLKGEN_BASE_ADDR + 0x84) = 0x01 ;//Reg_rst_alignment
HW32_REG(CLKGEN_BASE_ADDR + 0x88) = 0x01 ;//Reg_rst_sdram
HW32_REG(CLKGEN_BASE_ADDR + 0x8c) = 0x01 ;//Reg_rst_DMA
HW32_REG(CLKGEN_BASE_ADDR + 0x90) = 0x01 ;//Reg_rst_fifo
HW32_REG(CLKGEN_BASE_ADDR + 0x94) = 0x01 ;//Reg_rst_dbgctl
HW32_REG(CLKGEN_BASE_ADDR + 0x98) = 0x01 ;//Osc_bypass

printf(" CLK write \n");

temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x00) ;//N
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x04) ;//M
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x08) ;//Pll_bypass
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x0c) ;//OD
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x10) ;//Sel_Clk_ahb
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x14) ;//Sel_Clk_fm
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x18) ;//Sel_Clk_wm
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x1c) ;//Sel_Clk_bbqs
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x20) ;//Sel_Clk_act
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x24) ;//Sel_Clk_pooling
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x28) ;//Sel_Clk_dc
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x2c) ;//Sel_Clk_compress
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x30) ;//Sel_Clk_pe
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x34) ;//Sel_Clk_ce
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x38) ;//Sel_clk_alignment
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x3c) ;//Sel_Clk_sdram
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x40) ;//Sel_Clk_DMA
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x44) ;//Sel_Clk_fifo
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x48) ;//Sel_Clk_dbgctl
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x4c) ;//Divide_N1
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x50) ;//Divide_N2
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x54) ;//Divide_N3
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x58) ;//Divide_N4
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x5c) ;//Reg_rst_ahb
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x60) ;//Reg_rst_fm
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x64) ;//Reg_rst_wm
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x68) ;//Reg_rst_bbqs
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x6c) ;//Reg_rst_act
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x70) ;//Reg_rst_pooling
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x74) ;//Reg_rst_dc
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x78) ;//Reg_rst_compress
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x7c) ;//Reg_rst_pe
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x80) ;//Reg_rst_ce
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x84) ;//Reg_rst_alignment
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x88) ;//Reg_rst_sdram
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x8c) ;//Reg_rst_DMA
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x90) ;//Reg_rst_fifo
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x94) ;//Reg_rst_dbgctl
temp_data = HW32_REG(CLKGEN_BASE_ADDR + 0x98) ;//Osc_bypass

printf(" CLK read \n");

  //SDRAM  //passed
	HW32_REG(SDRAM_BASE_ADDR + 0x00) = 0x02 ;   //weight0
  HW32_REG(SDRAM_BASE_ADDR + 0x04) = 0x04 ;   //weight1
  HW32_REG(SDRAM_BASE_ADDR + 0x08) = 0x06 ;   //weight2
  HW32_REG(SDRAM_BASE_ADDR + 0x0C) = 0x08 ;   //weight3
  HW32_REG(SDRAM_BASE_ADDR + 0x10) = 0x0A ;   //weight4
  HW32_REG(SDRAM_BASE_ADDR + 0x14) = 0x0C ;   //weight5
  HW32_REG(SDRAM_BASE_ADDR + 0x18) = 0x10 ;   //weight6
  HW32_REG(SDRAM_BASE_ADDR + 0x1C) = 0x12 ;   //weight7

  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x00);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x04);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x08);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x0C);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x10);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x14);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x18);
  temp_data = HW32_REG(SDRAM_BASE_ADDR + 0x1C);


/*
  //WM   //not passed //can not  write data to reg; yinjianfei write the code himself
	HW32_REG(WM_BASE_ADDR) = 0x8a;
	temp_data = HW32_REG(WM_BASE_ADDR);
*/
	//PE  passed
	HW32_REG(PE_BASE_ADDR) = 0x1;                  //COM-en
	HW32_REG(PE_BASE_ADDR + 0x04) = 0xA2;	         //CE-kernel_stride
	HW32_REG(PE_BASE_ADDR + 0x08) = 0x0;           //PE-fsign
	
	temp_data = HW32_REG(PE_BASE_ADDR);
	temp_data = HW32_REG(PE_BASE_ADDR + 0x04);
	temp_data = HW32_REG(PE_BASE_ADDR + 0x08);

	//PPU passed
  HW32_REG(PPU_BASE_ADDR) = 0x50008A0;      //sys_bbqs
	HW32_REG(PPU_BASE_ADDR + 0x04) = 0x402;   //dpadding
	HW32_REG(PPU_BASE_ADDR + 0x08) = 0x0;     //act
  HW32_REG(PPU_BASE_ADDR + 0x0C) = 0x3;     //poo
	HW32_REG(PPU_BASE_ADDR + 0x10) = 0x6017;  //datacapture
  HW32_REG(PPU_BASE_ADDR + 0x14) = 0x1;     //bbqs_cvt

  temp_data = HW32_REG(PPU_BASE_ADDR);
  temp_data = HW32_REG(PPU_BASE_ADDR + 0x04);
  temp_data = HW32_REG(PPU_BASE_ADDR + 0x08);	
	temp_data = HW32_REG(PPU_BASE_ADDR + 0x0C);
  temp_data = HW32_REG(PPU_BASE_ADDR + 0x10);
  temp_data = HW32_REG(PPU_BASE_ADDR + 0x14);
	
	//FM  //config1-4 passed //da_tr_wr_cnt dont know
  HW32_REG(FM_BASE_ADDR) = 0x5220001;         //configure1
  HW32_REG(FM_BASE_ADDR+0x04) = 0x5d005d;     //configure2
  HW32_REG(FM_BASE_ADDR+0x08) = 0x1010101;    //configure3
  HW32_REG(FM_BASE_ADDR+0x0C) = 0x0;          //configure4  
	
  temp_data = HW32_REG(FM_BASE_ADDR+0x10);    //da_tr_wr_cnt
	
	//
  temp_data=0;
  hardfault_occurred = 0;
  hardfault_expected = 0;



  /* Generate test pass/fail and return value */
  if (err_code==0) {
    printf ("\n** TEST PASSED **\n");
  } else {
    printf ("\n** TEST FAILED **, Error code = (0x%x)\n", err_code);
  }
  UartEndSimulation();
  return 0;
}
