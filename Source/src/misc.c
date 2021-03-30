#include "misc.h"
#include "init.h"
#include "CM3DS_MPS2.h"

void uart_init(double freq_mhz , int baud_rate){
	
		CM3DS_MPS2_UART0->BAUDDIV = (int)(freq_mhz*1000*1000 / baud_rate); //SystemCoreClock / baud_rate;  
		
    CM3DS_MPS2_UART0->CTRL = ((1ul <<  0) |              /* TX enable */
                              (1ul <<  1) );             /* RX enable */
}