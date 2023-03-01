/* 
 * File:   uart.h
 * Author: DELL
 *
 * Created on February 16, 2023, 3:43 PM
 */

#ifndef UART_H
#define	UART_H

#include <p18f4620.h>

#define UART_BAUDRATE           9600

#define TRISPIN_OUT_UART        TRISCbits.RC6
#define TRISPIN_IN_UART         TRISCbits.RC7


void UART_Init(void);

void UART_SendChar(unsigned char data);
void UART_SendString(const rom unsigned char *str);
void UART_SendNum(unsigned char num);
void UART_Isr(void);

#endif	/* UART_H */

