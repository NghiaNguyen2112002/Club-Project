/*
 * File:   main.c
 * Author: DELL
 *
 * Created on February 7, 2023, 2:18 PM
 */


#include "main.h"
#include "fsm.h"

void SYS_Init(void);

void Delay_ms(int value);

void main(void) {

    SYS_Init();
    
    LCD_PrintStringBuffer(0, 0, " TRAFFIC  LIGHT ");
    LCD_DisplayScreen();
    Delay_ms(2000);
    LCD_ClearBuffer();
    
    while(1){
        while(!flag_timer3);
        flag_timer3 = 0;
        
        
        KEY_Reading();     
        
        if(_counterLight_1 >= 5) _counterLight_1 -= 5;
        if(_counterLight_2 >= 5) _counterLight_2 -= 5;
        if(_timeOutAjustMode >= 5) _timeOutAjustMode -= 5; 
        
        
        FSM_TrafficLight();
        LCD_DisplayScreen();
    }
    return;
}

void SYS_Init(void){    
//    Delay_ms(1000);

    LCD_Init();
    INT_Init();
    KEY_Init();
    FSM_Init();
    OUT_Init();
    
//    timer clock is 1Mhz
//    TMR0_Init(4695);            //1ms
//    TMR1_Init(9390);            //2ms
    TMR3_Init(46950);           //10ms

//    TMR0_SetTime_ms(1000);      //1s
//    TMR1_SetTime_ms(10);        //10ms
    TMR3_SetTime_ms(50);        //50ms
}


void Delay_ms(int value)
{
	int i,j;
	for(i = 0; i < value; i++)
		for(j = 0; j < 160; j++);
}