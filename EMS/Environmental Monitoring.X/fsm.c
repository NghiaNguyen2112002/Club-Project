#include "fsm.h"

enum ModeClockControl mode;
enum ModeDataControl mode_data;

void FSM_Init(void){
    mode = INIT;
    mode_data = INIT_;
}

void DisplayTime(void){
    LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
    LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
    LCD_PrintNumBuffer(0,INDEX_SEC_LCD, _second);
        
    LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
    LCD_PrintNumBuffer(1, INDEX_MONTH_LCD, _month);
    LCD_PrintNumBuffer(1, INDEX_YEAR_LCD, _year);
    
}

void FSM_ClockControl(void){
    switch(mode){
        case INIT:
            LCD_PrintStringBuffer(0, 0, SCREEN_NORMAL_DISPLAY_0);
            LCD_PrintStringBuffer(1, 0, SCREEN_NORMAL_DISPLAY_1);
//            "  :  :  "        //  "18:13:50"  
//            "  /  /  "        //  "30/08/23"
            
            DisplayTime();
            _flag_get_time = 1;
            mode = NORMAL_DISPLAY;
            break;
        case NORMAL_DISPLAY:
            if(!_counter_display_time){
                _counter_display_time = TIME_DISPLAY_TIME;
                DisplayTime();
            }
            
            if(KEY_IsPressed(MODE_BUTTON)){
                _flag_get_time = 0;
                DisplayTime();
                mode = ADJUST_TIME;
            }
            break;
        case ADJUST_TIME:
            _flag_get_time = 0;
            _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
            mode = ADJUST_HOUR;
            
            break;
        case ADJUST_HOUR:
            if(_counter_blinking == 0){
                _counter_blinking = TIME_BLINKING;
                if(_flag_blinking){
                    _flag_blinking = 0;
                    LCD_PrintStringBuffer(0, INDEX_HOUR_LCD, "  ");
                }
                else if(!_flag_blinking){
                    _flag_blinking = 1;
                    LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _hour = _hour > 0 ? _hour - 1 : 23;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _hour = _hour < 23 ? _hour + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_MIN;
            }
            else if(_counter_time_out == 0){
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);
                mode = INIT;
            } 
            break;
        case ADJUST_MIN:
            if(_counter_blinking == 0){
                _counter_blinking = TIME_BLINKING;
                if(_flag_blinking){
                    _flag_blinking = 0;
                    LCD_PrintStringBuffer(0, INDEX_MIN_LCD, "  ");
                }
                else if(!_flag_blinking){
                    _flag_blinking = 1;
                    LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _minute = _minute > 0 ? _minute - 1 : 59;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _minute = _minute < 59 ? _minute + 1 :  0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_DATE;
            }
            else if(_counter_time_out == 0){
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);
                mode = INIT;
            }
            break;
        case ADJUST_DATE:
            if(_counter_blinking == 0){
                _counter_blinking = TIME_BLINKING;
                if(_flag_blinking){
                    _flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_DATE_LCD, "  ");
                }
                else if(!_flag_blinking){
                    _flag_blinking = 1;
                    LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _date = _date > 0 ? _date - 1 : 31;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _date = _date < 31 ? _date + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
                I2C_WriteDS1307(ADDRESS_DATE, _date);
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_MONTH;
            }
            else if(_counter_time_out == 0){
                I2C_WriteDS1307(ADDRESS_DATE, _date);
                mode = INIT;
            }

            break;
        case ADJUST_MONTH:
            if(_counter_blinking == 0){
                _counter_blinking = TIME_BLINKING;
                if(_flag_blinking){
                    _flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_MONTH_LCD, "  ");
                }
                else if(!_flag_blinking){
                    _flag_blinking = 1;
                    LCD_PrintNumBuffer(1, INDEX_MONTH_LCD, _month);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _month = _month > 1 ? _month - 1 : 1;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _month = _month < 12 ? _month + 1 : 12;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                I2C_WriteDS1307(ADDRESS_MONTH, _month);
                LCD_PrintNumBuffer(1, INDEX_MONTH_LCD, _month);
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_YEAR;
            }
            else if(_counter_time_out == 0){
                I2C_WriteDS1307(ADDRESS_MONTH, _month);
                mode = INIT;
            }
            break;
        case ADJUST_YEAR:
            if(_counter_blinking == 0){
                _counter_blinking = TIME_BLINKING;
                if(_flag_blinking){
                    _flag_blinking = 0;
                    LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "  ");
                }
                else if(!_flag_blinking){
                    _flag_blinking = 1;
                    LCD_PrintNumBuffer(1, INDEX_YEAR_LCD, _year);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _year = _year > 0 ? _year - 1 : 99;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                _year = _year < 99 ? _year + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(1, INDEX_YEAR_LCD, _year);
                I2C_WriteDS1307(ADDRESS_YEAR, _year);
                _counter_time_out = TIME_OUT_FOR_ADJUSTMENT;
                mode = INIT;
            }
            else if(_counter_time_out == 0){
                I2C_WriteDS1307(ADDRESS_YEAR, _year);
                mode = INIT;
            }
            break;
        default:
            mode = INIT;
            break;
    }
}




void FSM_DataControl(void){
    switch(mode_data){
        case INIT_:
            LCD_PrintStringBuffer(0, 8, SCREEN_DATA_DISPLAY_0);
            LCD_PrintStringBuffer(1, 8, SCREEN_DATA_DISPLAY_1);
            
            LCD_PrintCharBuffer(0, INDEX_CELSIUS_SIGN_LCD, 0xDF);
            mode_data = DISPLAY_DATA;
            break;
        case DISPLAY_DATA:
            if(!_counter_reading_data){
                _counter_reading_data = TIME_READING_DATA;
                LCD_PrintNumBuffer(0, 8, DHT11_Read());
                              
                LCD_PrintNumBuffer(0, INDEX_TEMP_LCD, DHT11_ReturnTemp_Integral());
                LCD_PrintNumBuffer(1, INDEX_HUMID_LCD, DHT11_ReturnHumid_Integral());
                mode_data = SEND_DATA;
            }
            break;
        case SEND_DATA:
            UART_SendChar("!");
            
            UART_SendString(":1:TEMP:");
            UART_SendNum(DHT11_ReturnTemp_Integral());
            UART_SendString(":HUMID:");
            UART_SendNum(DHT11_ReturnHumid_Integral());
            
            UART_SendChar(":#");
            
            mode_data = DISPLAY_DATA;
            break;
        default:
            mode_data = INIT_;
            break;
    }
}
    