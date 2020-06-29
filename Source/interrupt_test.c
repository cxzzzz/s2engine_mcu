
#include <stdio.h>
#include <stdint.h>


#include "DS_CM3.h"
#include "RTE_Components.h"             // Component selection
#include "Driver_USART.h"
#include "Board_LED.h"
#include "Board_Buttons.h"

#include "assert.h"


char message[] = "Hello World\n\r";


void ledon(void){
	LED_On(0);
}

int main(void)
{
	SystemInit();
	
	
	LED_Initialize();
	
	Buttons_Initialize();
	
	
	NVIC_SetPriorityGrouping(5);
	
	DS_CM3_GPIO0->INTENSET = DS_CM3_GPIO_INTENCLR_Msk;
	DS_CM3_GPIO0->INTTYPESET = DS_CM3_GPIO_INTTYPESET_Msk;
	DS_CM3_GPIO0->OUTENCLR = DS_CM3_GPIO_OUTENCLR_Msk;
	DS_CM3_GPIO0->DATA = 0x1234;
	
	
	NVIC_SetPriority(GPIO0_0_IRQn,0xc);
	
	NVIC_EnableIRQ(GPIO0_0_IRQn);
	
	GPIO0
}

void GPIO0_0_Handler(void){
	static int i = 0;
	if( i == 0)
		LED_On(0);
	else
		LED_Off(0);
	i = ~i;
	return;
}