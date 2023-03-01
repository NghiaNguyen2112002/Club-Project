/*
 * File:   main.c
 * Author: DELL
 *
 * Created on February 23, 2023, 9:54 PM
 */


#include "main.h"


void SYS_Init(void);
void SetupTimeForFirstProgram(void);

void Delay_ms(int value);

void main(void) {
    
    SYS_Init();
    SetupTimeForFirstProgram();
    
    LCD_PrintStringBuffer(0, 0, " TASK  18/02/23 ");
    LCD_DisplayScreen();
    Delay_ms(2000);
    
    LCD_ClearBuffer();
    LCD_DisplayScreen();

    
    while(1){
        while(!flag_timer3);
        flag_timer3 = 0;
        
        KEY_Reading();
        
        if(_time_change_screen >= 5) _time_change_screen -= 5;
        if(_time_to_read_RTL >= 5) _time_to_read_RTL -= 5;
        if(_time_blinking >= 5) _time_blinking -= 5;
        if(_timeout >= 5) _timeout -= 5;
        
//        FSM_Control();
//        LCD_PrintNumBuffer(0, 0, ADC_Read(0));
        LCD_DisplayScreen();
        
    }
    return;
}


void SYS_Init(void){

    LCD_Init();
    INT_Init();
    KEY_Init();
    I2C_Init();
    ADC_Init();
    Delay_ms(1000);
    FSM_Init();
    
//    timer clock is 1Mhz
//    TMR0_Init(4695);            //1ms
//    TMR1_Init(9390);            //2ms
    TMR3_Init(46950);           //10ms

//    TMR0_SetTime_ms(1000);      //1s
//    TMR1_SetTime_ms(10);        //10ms
    TMR3_SetTime_ms(50);        //50ms
    
    Create_AlarmIcon();
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


void Delay_ms(int value)
{
	int i,j;
	for(i = 0; i < value; i++)
		for(j = 0; j < 160; j++);
}