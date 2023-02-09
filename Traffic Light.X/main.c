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
    Delay_ms(100);
    
    while(1){
        if(flag_timer0){
            flag_timer0 = 0;
            if(_counterLight_1 > 0) _counterLight_1--;
            if(_counterLight_2 > 0) _counterLight_2--;
            if(_timeOutAjustMode > 0) _timeOutAjustMode--;
            _flagEvery1Sec = 1;
        }
        if(flag_timer1){
            flag_timer1 = 0;
            KEY_Reading();            
        }
        if(flag_timer3){
            flag_timer3 = 0;
            LCD_DisplayScreen();
        }
        FSM_TrafficLight();
    }
    return;
}

void SYS_Init(void){
//    internal OSC 4MHz
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
//    OSCCONbits.SCS1 = 1;        //internal clock
    
//    Delay_ms(1000);

    LCD_Init();
    INT_Init();
    KEY_Init();
    FSM_Init();
    OUT_Init();
    
//    timer clock is 1Mhz
    TMR0_Init(4695);            //1ms
    TMR1_Init(9390);            //2ms
    TMR3_Init(46950);           //10ms

    TMR0_SetTime_ms(1000);      //1s
    TMR1_SetTime_ms(10);        //10ms
    TMR3_SetTime_ms(50);        //50ms
}


void Delay_ms(int value)
{
	int i,j;
	for(i = 0; i < value; i++)
		for(j = 0; j < 160; j++);
}