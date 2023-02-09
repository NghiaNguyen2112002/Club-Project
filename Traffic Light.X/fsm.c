#include "fsm.h"
#include "global.h"
#include "button_matrix.h"

enum MODE mode;
            
void FSM_Init(void){
    mode = INIT;
}  

void FSM_TrafficLight(void){
    switch(mode){
        case INIT:
            LCD_PrintStringBuffer(0, 0, SCREEN_MANUAL_0);
            LCD_PrintStringBuffer(1, 0, SCREEN_MANUAL_1);
            mode = MANUAL;
            break;
        case MANUAL:
            if(KEY_IsPressed(MODE_BUTTON)){
                LCD_ClearBuffer();
                mode = START_AUTO;
            }
            else if(KEY_IsPressed_ms(MODE_BUTTON, 1000)) {
                LCD_ClearBuffer();
                LCD_PrintStringBuffer(0, 0, SCREEN_ADJUST_0);
                LCD_PrintStringBuffer(1, 0, SCREEN_ADJUST_1);
                _timeOutAjustMode = 10;             //10s
                mode = ADJUST;
            }   
            else if(KEY_IsPressed(RED_1_BUTTON)) mode = MANUAL_RED_1;
            else if(KEY_IsPressed(GREEN_1_BUTTON)) mode = MANUAL_GREEN_1;
            else if(KEY_IsPressed(YELLOW_1_BUTTON)) mode = MANUAL_YELLOW_1;
            else if(KEY_IsPressed(RED_2_BUTTON)) mode = MANUAL_RED_2;
            else if(KEY_IsPressed(GREEN_2_BUTTON)) mode = MANUAL_GREEN_2;
            else if(KEY_IsPressed(YELLOW_2_BUTTON)) mode = MANUAL_YELLOW_2;
            break;
        case START_AUTO:
            LCD_PrintStringBuffer(0, 0, SCREEN_AUTO_RED_1);
            LCD_PrintStringBuffer(1, 0, SCREEN_AUTO_GREEN_2);
            _counterLight_1 = _timeRed;
            _counterLight_2 = _timeGreen;
            mode = AUTO_RED_GREEN;
            
            break;
        case STOP_AUTO:
            mode = INIT;
            break;
        case MANUAL_RED_1:
            LCD_PrintStringBuffer(0, 0, SCREEN_MANUAL_RED_1);
            OUT_OnRed_1();
            mode = MANUAL;
            
            break;
        case MANUAL_GREEN_1:
            LCD_PrintStringBuffer(0, 0, SCREEN_MANUAL_GREEN_1);
            OUT_OnGreen_1();
            mode = MANUAL;
            
            break;
        case MANUAL_YELLOW_1:
            LCD_PrintStringBuffer(0,0, SCREEN_MAUAL_YELLOW_1);
            OUT_OnYellow_1();
            mode = MANUAL;
            
            break;
        case MANUAL_RED_2:
            LCD_PrintStringBuffer(0, 8, SCREEN_MANUAL_RED_2);
            OUT_OnRed_2();
            mode = MANUAL;
            
            break;
        case MANUAL_GREEN_2:
            LCD_PrintStringBuffer(0, 8, SCREEN_MANUAL_GREEN_2);
            OUT_OnGreen_2();
            mode = MANUAL;
            
            break;
        case MANUAL_YELLOW_2:
            LCD_PrintStringBuffer(0, 8, SCREEN_MANUAL_YELLOW_2);
            OUT_OnYellow_2();
            mode = MANUAL;
            
            break;    
        case AUTO_RED_GREEN:
            OUT_OnRed_1();
            OUT_OnGreen_2();
            
            if(_flagEvery1Sec){
                _flagEvery1Sec = 0;
                LCD_PrintNumBuffer(0, 8, _counterLight_1);
                LCD_PrintNumBuffer(1, 8, _counterLight_2);
            }
            if(_counterLight_2 == 0) {
                LCD_PrintStringBuffer(0, 0, SCREEN_AUTO_RED_1);
                LCD_PrintStringBuffer(1, 0, SCREEN_AUTO_YELLOW_2);
                _counterLight_2 = _timeYellow;
                mode = AUTO_RED_YELLOW;
            }                   
            if(KEY_IsPressed(MODE_BUTTON)) mode = STOP_AUTO;
            break;
        case AUTO_RED_YELLOW:
            OUT_OnRed_1();
            OUT_OnYellow_2();
            
            if(_flagEvery1Sec){
                _flagEvery1Sec = 0;
                LCD_PrintNumBuffer(0, 8, _counterLight_1);
                LCD_PrintNumBuffer(1, 8, _counterLight_2);
            }
            if(_counterLight_1 == 0){
                LCD_PrintStringBuffer(0, 0, SCREEN_AUTO_GREEN_1);
                LCD_PrintStringBuffer(1, 0, SCREEN_AUTO_RED_2);
                _counterLight_1 = _timeGreen;
                _counterLight_2 = _timeRed;
                mode = AUTO_GREEN_RED;
            }
            if(KEY_IsPressed(MODE_BUTTON)) mode = STOP_AUTO;
            break;
        case AUTO_GREEN_RED:
            OUT_OnGreen_1();
            OUT_OnRed_2();
            
            if(_flagEvery1Sec){
                _flagEvery1Sec = 0;
                LCD_PrintNumBuffer(0, 8, _counterLight_1);
                LCD_PrintNumBuffer(1, 8, _counterLight_2);
            }
            if(_counterLight_1 == 0){
                LCD_PrintStringBuffer(0, 0, SCREEN_AUTO_YELLOW_1);
                LCD_PrintStringBuffer(1, 0, SCREEN_AUTO_RED_2);
                _counterLight_1 = _timeYellow;
                mode = AUTO_YELLOW_RED;
            }
            if(KEY_IsPressed(MODE_BUTTON)) mode = STOP_AUTO;
            break;
        case AUTO_YELLOW_RED:
            OUT_OnYellow_1();
            OUT_OnRed_2();
            
            if(_flagEvery1Sec){
                _flagEvery1Sec = 0;
                LCD_PrintNumBuffer(0, 8, _counterLight_1);
                LCD_PrintNumBuffer(1, 8, _counterLight_2);
            }
            if(_counterLight_2 == 0){
                LCD_PrintStringBuffer(0, 0, SCREEN_AUTO_RED_1);
                LCD_PrintStringBuffer(1, 0, SCREEN_AUTO_GREEN_2);
                _counterLight_1 = _timeRed;
                _counterLight_2 = _timeGreen;
                mode = AUTO_RED_GREEN;
            }
            if(KEY_IsPressed(MODE_BUTTON)) mode = STOP_AUTO;
            break;
        case ADJUST:
            if(KEY_IsPressed(INC_BUTTON)){
                LCD_ClearBuffer();
                LCD_PrintStringBuffer(0, 0, SCREEN_ADJUST_GREEN_0);
                LCD_PrintStringBuffer(0, 1, SCREEN_ADJUST_GREEN_1);
                LCD_PrintNumBuffer(1, 8, _timeGreen);

                _timeOutAjustMode = 10;                 //10s
                mode = ADJUST_GREEN;
            }          
            else if(KEY_IsPressed(DEC_BUTTON)){
                LCD_ClearBuffer();
                LCD_PrintStringBuffer(0, 0, SCREEN_ADJUST_YELLOW_0);
                LCD_PrintStringBuffer(0, 1, SCREEN_ADJUST_YELLOW_1);
                LCD_PrintNumBuffer(1, 8, _timeYellow);
                
                _timeOutAjustMode = 10;                 //10s
                mode = ADJUDT_YELLOW;
            }
            else if(KEY_IsPressed(MODE_BUTTON) || _timeOutAjustMode == 0) mode = INIT;
            
            break;
        case ADJUST_GREEN:
            if(KEY_IsPressed(DEC_BUTTON)) {
                _timeGreen--;
                _timeOutAjustMode = 10;                 //10s
                LCD_PrintNumBuffer(1, 8, _timeGreen);
            }
            else if(KEY_IsPressed(INC_BUTTON)) {
                _timeGreen++;
                _timeOutAjustMode = 10;                 //10s
                LCD_PrintNumBuffer(1, 8, _timeGreen);
            }
            else if(KEY_IsPressed(MODE_BUTTON) || _timeOutAjustMode == 0) {
                _timeRed = _timeGreen + _timeYellow;
                mode = INIT;
            }
            break;
        case ADJUDT_YELLOW:
            if(KEY_IsPressed(DEC_BUTTON)) {
                _timeYellow--;
                _timeOutAjustMode = 10;                 //10s
                LCD_PrintNumBuffer(1, 8, _timeYellow);
            }
            else if(KEY_IsPressed(INC_BUTTON)) {
                _timeYellow++;
                _timeOutAjustMode = 10;                 //10s
                LCD_PrintNumBuffer(1, 8, _timeYellow);
            }
            else if(KEY_IsPressed(MODE_BUTTON) || _timeOutAjustMode == 0) {
                _timeRed = _timeGreen + _timeYellow;
                mode = INIT;
            }
            break;
        default:
            mode = INIT;
            break;
    }
}
