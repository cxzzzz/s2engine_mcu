#ifndef _usart_H
#define _usart_H


#include "stdint.h"
#include "stdio.h" 

#define USART1_REC_LEN		200  	//�����������ֽ��� 200

extern uint8_t  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern uint16_t USART1_RX_STA;         		//����״̬���


void USART1_Init(uint32_t bound);


#endif

