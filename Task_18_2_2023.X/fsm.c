#include "fsm.h"

unsigned char flag_blinking;
unsigned char mode_fsm;


void RTC_GetDateTime(void){
    _second = I2C_ReadDS1307(ADDRESS_SECOND);
    _minute = I2C_ReadDS1307(ADDRESS_MINUTE);
    _hour = I2C_ReadDS1307(ADDRESS_HOUR);
    _date = I2C_ReadDS1307(ADDRESS_DATE);
    _month = I2C_ReadDS1307(ADDRESS_MONTH);
    _year = I2C_ReadDS1307(ADDRESS_YEAR);
}

void PrintTime(void){
    LCD_PrintTimeBuffer(0, INDEX_HOUR_LCD, _hour);
    LCD_PrintTimeBuffer(0, INDEX_MIN_LCD, _minute);
    LCD_PrintTimeBuffer(0, INDEX_SEC_LCD, _second);
    LCD_PrintTimeBuffer(1, INDEX_DATE_LCD, _date);
    LCD_PrintTimeBuffer(1, INDEX_MON_LCD, _month);
    LCD_PrintTimeBuffer(1, INDEX_YEAR_LCD, _year);
}

void FSM_Init(void){
    flag_blinking = 0;
    mode_fsm = INIT;
}



void FSM_Control(void){
    switch(mode_fsm){
        case INIT:
            LCD_PrintStringBuffer(0, 0, SCREEN_TEMP_HUMID_0);
            LCD_PrintStringBuffer(1, 0, SCREEN_TEMP_HUMID_1);
            LCD_PrintCharBuffer(0, INDEX_CELSIUS_LCD, 0xDF);
            
            _time_change_screen = TIME_VIEW_HUMI_TEMP;
            mode_fsm = TEMP_HUMID_VIEW;
            break;
        case TEMP_HUMID_VIEW:
            _temp =  ADC_Read(0);
            LCD_PrintNumBuffer(0, INDEX_TEMP_LCD, _temp);
            LCD_PrintNumBuffer(1, INDEX_HUMI_LCD, _humid++);
            
            if(!_time_change_screen){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            }
            break;
        case TIME_VIEW:
            if(!_time_to_read_RTL){
                _time_to_read_RTL = TIME_TO_READ_RTL;
                
                RTC_GetDateTime();
                PrintTime();             
            }
            if(KEY_IsPressed(MODE_BUTTON)){
                mode_fsm = ADJUST_TIME;
            }
            if(!_time_change_screen){
                LCD_PrintStringBuffer(0, 0, SCREEN_SIM_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_SIM_1);
                
                _time_change_screen = TIME_VIEW_SIM;
                mode_fsm = SIM_VIEW;
            }
            break;
        case SIM_VIEW:
            
            if(!_time_change_screen){
                mode_fsm = INIT;
            }
            break;
        case ADJUST_TIME:
            _timeout = TIME_OUT_ADJUST_TIME;
            mode_fsm = ADJUST_HOUR;
            break;
        case ADJUST_HOUR:
            if(!_time_blinking){
                _time_blinking = TIME_BLINKING;
                if(flag_blinking){
                    flag_blinking = 0;
                    LCD_PrintStringBuffer(0, INDEX_HOUR_LCD, "  ");
                }
                else{
                    flag_blinking = 1;
                    LCD_PrintTimeBuffer(0, INDEX_HOUR_LCD, _hour);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _hour = _hour > 0 ? _hour - 1 : 23;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _hour = _hour < 23 ? _hour + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintTimeBuffer(0, INDEX_HOUR_LCD, _hour);
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);
                _timeout = TIME_OUT_ADJUST_TIME;
                mode_fsm = ADJUST_MIN;
            }
            else if(!_timeout){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);

                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            }
            break;
        case ADJUST_MIN:
            if(!_time_blinking){
                _time_blinking = TIME_BLINKING;
                if(flag_blinking){
                    flag_blinking = 0;
                    LCD_PrintStringBuffer(0, INDEX_MIN_LCD, "  ");
                }
                else{
                    flag_blinking = 1;
                    LCD_PrintTimeBuffer(0, INDEX_MIN_LCD, _minute);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _minute = _minute > 0 ? _minute - 1 : 59;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _minute = _minute < 59 ? _minute + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintTimeBuffer(0, INDEX_MIN_LCD, _minute);
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);
                _timeout = TIME_OUT_ADJUST_TIME;
                mode_fsm = ADJUST_DATE;
            }
            else if(!_timeout){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);

                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            }
            break;
        case ADJUST_DATE:
            if(!_time_blinking){
                _time_blinking = TIME_BLINKING;
                if(flag_blinking){
                    flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_DATE_LCD, "  ");
                }
                else{
                    flag_blinking = 1;
                    LCD_PrintTimeBuffer(1, INDEX_DATE_LCD, _date);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _date = _date > 0 ? _date - 1 : 31;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _date = _date < 31 ? _date + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintTimeBuffer(1, INDEX_DATE_LCD, _date);
                I2C_WriteDS1307(ADDRESS_DATE, _date);
                _timeout = TIME_OUT_ADJUST_TIME;
                mode_fsm = ADJUST_MONTH;
            }
            else if(!_timeout){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                I2C_WriteDS1307(ADDRESS_DATE, _date);

                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            } 
            break;
        case ADJUST_MONTH:
            if(!_time_blinking){
                _time_blinking = TIME_BLINKING;
                if(flag_blinking){
                    flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_MON_LCD, "  ");
                }
                else{
                    flag_blinking = 1;
                    LCD_PrintTimeBuffer(1, INDEX_MON_LCD, _month);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _month = _month > 1 ? _month - 1 : 12;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _month = _month < 12 ? _month + 1 : 1;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintTimeBuffer(1, INDEX_MON_LCD, _month);
                I2C_WriteDS1307(ADDRESS_MONTH, _month);
                _timeout = TIME_OUT_ADJUST_TIME;
                mode_fsm = ADJUST_YEAR;
            }
            else if(!_timeout){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                I2C_WriteDS1307(ADDRESS_MONTH, _month);

                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            } 
            break;
        case ADJUST_YEAR:
            if(!_time_blinking){
                _time_blinking = TIME_BLINKING;
                if(flag_blinking){
                    flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "  ");
                }
                else{
                    flag_blinking = 1;
                    LCD_PrintTimeBuffer(1, INDEX_YEAR_LCD, _year);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _year = _year > 0 ? _year - 1 : 99;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _timeout = TIME_OUT_ADJUST_TIME;
                _year = _year < 99 ? _year + 1 : 0;
            }
            else if(!_timeout || KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintStringBuffer(0, 0, SCREEN_TIME_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TIME_1);
                
                I2C_WriteDS1307(ADDRESS_YEAR, _year);

                _time_change_screen = TIME_VIEW_RTL;
                mode_fsm = TIME_VIEW;
            } 
            break;
        default:
            mode_fsm = INIT;
            break;
    }
}
