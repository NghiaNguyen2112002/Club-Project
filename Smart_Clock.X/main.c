/*
 * File:   main.c
 * Author: DELL
 *
 * Created on February 9, 2023, 4:16 PM
 */

#include "main.h"
#include "fsm.h"


#define TEST_ICON           0




void SYS_Init(void);
void SetupTimeForFirstProgram(void);
void RTC_GetDateTime(void);
void Create_AlarmIcon(void);


void Delay_ms(int value);

void main(void) {

    SYS_Init();
    SetupTimeForFirstProgram();
    
    LCD_PrintStringBuffer(0, 0, "  SMART  CLOCK  ");
    LCD_DisplayScreen();
    Delay_ms(2000);
    Create_AlarmIcon();
    
    LCD_ClearBuffer();
    Delay_ms(1000);
    
    LCD_PrintCharBuffer(0, 6, 0);
    LCD_PrintCharBuffer(0, 7, 1);
    LCD_PrintCharBuffer(0, 8, 2);
    LCD_PrintCharBuffer(1, 6, 3);
    LCD_PrintCharBuffer(1, 7, 4);
    LCD_PrintCharBuffer(1, 8, 5);
    
    LCD_DisplayScreen();
    Delay_ms(2000);
    
    while(1){
        while(!flag_timer3);
        flag_timer3 = 0;
        
        KEY_Reading();     
        
        
        if(_counterTimeOut >= 50) _counterTimeOut -= 50;
        if(_counterEvery_ms >= 50) _counterEvery_ms -= 50;
        if(_counterFrameAnimation >= 50) _counterFrameAnimation -= 50;
        
        if(_flagGetTime) RTC_GetDateTime();
        
        FSM_AlarmControl();
        LCD_DisplayScreen();
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
//    TMR0_Init(4695);            //1ms
//    TMR1_Init(9390);            //2ms
    TMR3_Init(46950);           //10ms

//    TMR0_SetTime_ms(1000);      //1s
//    TMR1_SetTime_ms(10);        //10ms
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

void Create_AlarmIcon(void){
    LCD_CreateChar(0, alarm_1);
    LCD_CreateChar(1, alarm_2);
    LCD_CreateChar(2, alarm_3);
    LCD_CreateChar(3, alarm_4);
    LCD_CreateChar(4, alarm_5);
    LCD_CreateChar(5, alarm_6);
}

void Delay_ms(int value)
{
	int i,j;
	for(i = 0; i < value; i++)
		for(j = 0; j < 160; j++);
}