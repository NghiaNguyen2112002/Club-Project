/*
 * File:   main.c
 * Author: DELL
 *
 * Created on February 9, 2023, 4:16 PM
 */

#include "main.h"
#include "fsm.h"




unsigned char count = 0;


void SYS_Init(void);
void SetupTimeForFirstProgram(void);
void RTC_GetDateTime(void);


void Delay_ms(int value);

void main(void) {

    SYS_Init();
    SetupTimeForFirstProgram();
    
    LCD_PrintStringBuffer(0, 0, "  SMART  CLOCK  ");
    LCD_DisplayScreen();
    Delay_ms(2000);
    
    LCD_ClearBuffer();
    
    while(1){
        FSM_AlarmControl();
        if(flag_timer0){
            flag_timer0 = 0;
            _flagEverySec = 1;
            
            if(_counterTimeOut > 0) _counterTimeOut--;
        }
        if(flag_timer1){
            flag_timer1 = 0;
            KEY_Reading();            
        }
        if(flag_timer3){
            flag_timer3 = 0;
            
            if(_flagGetTime) RTC_GetDateTime();
            LCD_DisplayScreen();
            if(_counterEvery_ms > 0) _counterEvery_ms -= 50;
        }
    }
    
    return;
}

void SYS_Init(void){

    LCD_Init();
    INT_Init();
    KEY_Init();
    I2C_Init();
    FSM_Init();
//    timer clock is 1Mhz
    TMR0_Init(4695);            //1ms
    TMR1_Init(9390);            //2ms
    TMR3_Init(46950);           //10ms

    TMR0_SetTime_ms(1000);      //1s
    TMR1_SetTime_ms(10);        //10ms
    TMR3_SetTime_ms(50);        //50ms
}

void SetupTimeForFirstProgram(void)
{
    if(I2C_ReadDS1307(ADDRESS_FIRST_PROGRAM) != 0x60){   //random number
        I2C_WriteDS1307(ADDRESS_SECOND, 1);
        I2C_WriteDS1307(ADDRESS_MINUTE, 1);
        I2C_WriteDS1307(ADDRESS_HOUR, 1);
        I2C_WriteDS1307(ADDRESS_WEEK_DAY, 1);
        I2C_WriteDS1307(ADDRESS_DATE, 1);
        I2C_WriteDS1307(ADDRESS_MONTH, 1);
        I2C_WriteDS1307(ADDRESS_YEAR, 1);

        I2C_WriteDS1307(ADDRESS_FLAG_ALARM, 0);
        I2C_WriteDS1307(ADDRESS_HOUR_ALARM, 1);
        I2C_WriteDS1307(ADDRESS_MIN_ALARM, 1);
        
        I2C_WriteDS1307(ADDRESS_FIRST_PROGRAM, 0x60);
    }
    else RTC_GetDateTime();
    
}

void RTC_GetDateTime(void){
    _second = I2C_ReadDS1307(ADDRESS_SECOND);
    _minute = I2C_ReadDS1307(ADDRESS_MINUTE);
    _hour = I2C_ReadDS1307(ADDRESS_HOUR);
    _week_day = I2C_ReadDS1307(ADDRESS_WEEK_DAY);
    _date = I2C_ReadDS1307(ADDRESS_DATE);
    _month = I2C_ReadDS1307(ADDRESS_MONTH);
    _year = I2C_ReadDS1307(ADDRESS_YEAR);
    
    _hourAlarm = I2C_ReadDS1307(ADDRESS_HOUR_ALARM);
    _minuteAlarm = I2C_ReadDS1307(ADDRESS_MIN_ALARM);
    _flagAlarm = I2C_ReadDS1307(ADDRESS_FLAG_ALARM);

}


void Delay_ms(int value)
{
	int i,j;
	for(i = 0; i < value; i++)
		for(j = 0; j < 160; j++);
}