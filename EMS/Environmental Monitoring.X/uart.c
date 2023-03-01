#include "uart.h"

unsigned char data_receive;

void UART_Init(void){
    SPBRGH = 0;
//  Baud Rate =  FOSC/(64 ([SPBRGH:SPBRG] + 1)) 
//	when SYNC = 0, BRG16 = 1, BRGH = 0 => Baud Rate = F/[16(SPBRG + 1)]
//  => SPBRG = F/(16*Baud Rate) - 1
//    F = 20MHz
    SPBRG = 129;
//    SPBRG = (20000000 / 16) / UART_BAUDRATE - 1;
    TXSTAbits.TXEN = 1;     //transmit enable
    TXSTAbits.BRGH = 0;     //low speed
    BAUDCONbits.BRG16 = 1;  //16 bit generator
    
    TXSTAbits.SYNC = 0;     //asynchronous
    RCSTAbits.CREN = 1;     //enable receive
    RCSTAbits.SPEN = 1;     //serial port enable
    
    PIR1bits.RCIF = 0;      
    PIE1bits.RCIE = 1;
    IPR1bits.RCIP = 0;      //priority low
    
    TRISPIN_OUT_UART = 0;
    TRISPIN_IN_UART = 1;
    
}

void UART_SendChar(unsigned char data){
    while(PIR1bits.TXIF == 0);
    TXREG = data;
    PIR1bits.TXIF = 0;
}

void UART_SendString(const rom unsigned char *str){
    while(*str){
        UART_SendChar(*str++);
    }
}
    
void UART_SendNum(unsigned char num){
    UART_SendChar((num / 10) + '0');
    UART_SendChar((num % 10) + '0');
}

void UART_Isr(void){
    data_receive = RCREG;
}

