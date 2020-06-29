
#include <stdio.h>
#include "usart.h"


int fputc(int ch,FILE *p)  
{
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

int fgetc(FILE *p)
{

	while(USART_GetFlagStatus(DEBUG_USARTx , USART_FLAG_RXNE)==RESET);
	/* 返回值进行强制类型转换 */
	return (int)USART_ReceiveData(USART1);

}