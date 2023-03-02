#include "fsm.h"


enum Mode mode;

unsigned char temp;

void FSM_Init(void){
    mode = INIT;
}

void LCD_CreateAlarmNormal(void){
    LCD_CreateChar(0, alarm_1);
    LCD_CreateChar(1, alarm_2);
    LCD_CreateChar(2, alarm_3);
    LCD_CreateChar(3, alarm_4);
    LCD_CreateChar(4, alarm_5);
    LCD_CreateChar(5, alarm_6);
}

void LCD_CreateAlarmRing(void){
    LCD_CreateChar(0, alarm_ring_1);
    LCD_CreateChar(1, alarm_ring_2);
    LCD_CreateChar(2, alarm_ring_3);
    LCD_CreateChar(3, alarm_ring_4);
    LCD_CreateChar(4, alarm_ring_5);
    LCD_CreateChar(5, alarm_ring_6); 
}

void PrintWeekDay(unsigned char week_day){
        switch(week_day){
        case 1:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "MON");
            break;
        case 2:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "TUE");
            break;
        case 3:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "WEN");
            break;
        case 4:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "THU");
            break;
        case 5:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "FRI");
            break;
        case 6:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "SAT");
            break;
        case 7:
            LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "SUN");
            break;
    }
}

void DisplayTime(void){
    LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
    
    LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
    
    LCD_PrintNumBuffer(0,INDEX_SEC_LCD, _second);
    
    PrintWeekDay(_week_day);
    
    LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
    LCD_PrintNumBuffer(1, INDEX_MONTH_LCD, _month);
    
    LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "20");
    LCD_PrintNumBuffer(1, INDEX_YEAR_LCD+2, _year);
    
}

void FSM_AlarmControl(void){
    switch(mode){
        case INIT:
            LCD_PrintStringBuffer(0, 0, SCREEN_NORMAL_DISPLAY_0);
            LCD_PrintStringBuffer(1, 0, SCREEN_NORMAL_DISPLAY_1);
//                    "  :  :          "        //18:13:50
//                    "       /  /     "        //THU 30/08/2023
            
            if(_flagAlarm) {
                LCD_PrintStringBuffer(0, 10, "ON");
            }
            else if(_flagAlarm == 0){
                LCD_PrintStringBuffer(0, 10, "OFF");
            }
            DisplayTime();
            _flagGetTime = 1;
            mode = NORMAL_DISPLAY;
            
            break;
        case NORMAL_DISPLAY:
            DisplayTime();
//            compare alarm time
            if(_flagAlarm){
                if(_hour == _hourAlarm && _minute == _minuteAlarm && _second == 0){
                    LCD_PrintStringBuffer(0, 0, SCREEN_ALARM_GO_OFF_0);
                    LCD_PrintStringBuffer(1, 0, SCREEN_ALARM_GO_OFF_1);
                    _counterTimeOut = TIME_OUT_ALARM_GO_OFF;
                    mode = ALARM_GO_OFF;
                }
            }
            
            if(KEY_IsPressed(MODE_BUTTON)){
                DisplayTime();
                mode = ADJUST_TIME;
            }
            else if(KEY_IsPressed_ms(MODE_BUTTON, 1000)){   //press 1s
                LCD_PrintStringBuffer(0, 0, SCREEN_TURN_ALARM_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_TURN_ALARM_1);
                _counterTimeOut= TIME_OUT_FOR_ADJUSTMENT;
                _flagGetTime = 0;
                mode = SET_ALARM;
            }

            
            break;
        case ADJUST_TIME:
            _flagGetTime = 0;
            _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
            mode = ADJUST_HOUR;
            break; 
        case ADJUST_MIN:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(0, INDEX_MIN_LCD, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _minute = _minute > 0 ? _minute - 1 : 59;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _minute = _minute < 59 ? _minute + 1 :  0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(0, INDEX_MIN_LCD, _minute);
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_WEEK_DAY;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_MINUTE, _minute);
                mode = INIT;
            }
            break;

        case ADJUST_HOUR:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(0, INDEX_HOUR_LCD, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _hour = _hour > 0 ? _hour - 1 : 23;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _hour = _hour < 23 ? _hour + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(0, INDEX_HOUR_LCD, _hour);
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_MIN;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_HOUR, _hour);
                mode = INIT;
            }
            break;
        case ADJUST_WEEK_DAY:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, INDEX_WEEK_DAY_LCD, "   ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    PrintWeekDay(_week_day);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _week_day = _week_day > 1 ? _week_day - 1 : 7;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _week_day = _week_day < 7 ? _week_day + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                PrintWeekDay(_week_day);
                I2C_WriteDS1307(ADDRESS_WEEK_DAY, _week_day);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_DATE;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_WEEK_DAY, _week_day);
                mode = INIT;
            }

            break;
        case ADJUST_DATE:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, INDEX_DATE_LCD, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _date = _date > 0 ? _date - 1 : 31;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _date = _date < 31 ? _date + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(1, INDEX_DATE_LCD, _date);
                I2C_WriteDS1307(ADDRESS_DATE, _date);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_MONTH;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_DATE, _date);
                mode = INIT;
            }

            break;
        case ADJUST_MONTH:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, INDEX_MONTH_LCD, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(1, INDEX_MONTH_LCD, _month);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _month = _month > 1 ? _month - 1 : 1;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _month = _month < 12 ? _month + 1 : 12;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                I2C_WriteDS1307(ADDRESS_MONTH, _month);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = ADJUST_YEAR;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_MONTH, _month);
                mode = INIT;
            }

            break;
        case ADJUST_YEAR:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "    ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "20");
                    LCD_PrintNumBuffer(1, INDEX_YEAR_LCD+2, _year);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _year = _year > 0 ? _year - 1 : 99;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _year = _year < 99 ? _year + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintStringBuffer(1, INDEX_YEAR_LCD, "20");
                LCD_PrintNumBuffer(1, INDEX_YEAR_LCD+2, _year);
                I2C_WriteDS1307(ADDRESS_YEAR, _year);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = INIT;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_YEAR, _year);
                mode = INIT;
            }
            break;
        case SET_ALARM:
            if(KEY_IsPressed(DEC_BUTTON)){
                LCD_PrintStringBuffer(0, 0, SCREEN_TURN_ALARM_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_SET_ALARM_1);
//                    "   SET  ALARM   "  
//                    "H:      M:      "
                LCD_PrintNumBuffer(1, 3, _hourAlarm);
                LCD_PrintNumBuffer(1, 11, _minuteAlarm);
                _flagAlarm = 1;
                I2C_WriteDS1307(ADDRESS_FLAG_ALARM, _flagAlarm);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = SET_ALARM_HOUR;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _flagAlarm = 0;
                I2C_WriteDS1307(ADDRESS_FLAG_ALARM, _flagAlarm);
                mode = INIT;
            }
            else if(_counterTimeOut == 1) mode = INIT;
            break;
        case SET_ALARM_HOUR:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, 3, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(1, 3, _hourAlarm);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _hourAlarm = _hourAlarm > 0 ? _hourAlarm - 1 : 23;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _hourAlarm = _hourAlarm < 23 ? _hourAlarm + 1 : 0;
            }
            else if(KEY_IsPressed(MODE_BUTTON)){
                LCD_PrintNumBuffer(1, 3, _hourAlarm);
                I2C_WriteDS1307(ADDRESS_HOUR_ALARM, _hourAlarm);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = SET_ALARM_MIN;
            }
            else if(_counterTimeOut == 0){
                I2C_WriteDS1307(ADDRESS_HOUR_ALARM, _hourAlarm);
                mode = INIT;
            }
            break;
        case SET_ALARM_MIN:
            if(_counterEvery_ms == 0){
                _counterEvery_ms = 300;
                if(_flagBlinkCursor){
                    _flagBlinkCursor = 0;
                    LCD_PrintStringBuffer(1, 11, "  ");
                }
                else if(!_flagBlinkCursor){
                    _flagBlinkCursor = 1;
                    LCD_PrintNumBuffer(1, 11, _minuteAlarm);
                }
            }
            
            if(KEY_IsPressed(DEC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _minuteAlarm = _minuteAlarm > 0 ? _minuteAlarm - 1 : 59;
            }
            else if(KEY_IsPressed(INC_BUTTON)){
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                _minuteAlarm = _minuteAlarm < 59 ? _minuteAlarm + 1 :  0;
            }
            else if(KEY_IsPressed(MODE_BUTTON) || _counterTimeOut == 0){
                LCD_PrintNumBuffer(1, 11, _minute);
                I2C_WriteDS1307(ADDRESS_MIN_ALARM, _minuteAlarm);
                _counterTimeOut = TIME_OUT_FOR_ADJUSTMENT;
                mode = INIT;
            }

            break;
            case ALARM_GO_OFF:
                if(_counterFrameAnimation == 0){
                    _counterFrameAnimation = TIME_FRAME_RING_ANIMATION;
                    if(_flagFrameAnimation){
                        _flagFrameAnimation = 0;
                        LCD_CreateAlarmNormal();
                    }
                    else if(!_flagFrameAnimation){
                        _flagFrameAnimation = 1;
                        LCD_CreateAlarmRing();
                    }
                }
                
                LCD_PrintCharBuffer(0, 6, 0);
                LCD_PrintCharBuffer(0, 7, 1);
                LCD_PrintCharBuffer(0, 8, 2);
                LCD_PrintCharBuffer(1, 6, 3);
                LCD_PrintCharBuffer(1, 7, 4);
                LCD_PrintCharBuffer(1, 8, 5);
                if(KEY_IsPressed(MODE_BUTTON) || _counterTimeOut == 0) mode = INIT;
            break;
        default:
            mode = INIT;
            break;
    }
}
