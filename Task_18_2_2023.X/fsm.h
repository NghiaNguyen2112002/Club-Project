/* 
 * File:   fsm.h
 * Author: DELL
 *
 * Created on February 23, 2023, 10:24 PM
 */

#ifndef FSM_H
#define	FSM_H

#include <p18f4620.h>
#include "button_matrix.h"
#include "adc.h"
#include "lcd.h"
#include "global.h"
#include "i2c_ds1307.h"

//============FSM STATE============//
#define INIT                        0
#define TEMP_HUMID_VIEW             1
#define TIME_VIEW                   2
#define SIM_VIEW                    3
#define ADJUST_TIME                 4
#define ADJUST_HOUR                 5
#define ADJUST_MIN                  6
#define ADJUST_SECOND               7
#define ADJUST_DATE                 8
#define ADJUST_MONTH                9
#define ADJUST_YEAR                 10
//================================//

//============BUTTON==============//
//  [DEC]       [MODE]       [INC]
#define DEC_BUTTON                  8
#define MODE_BUTTON                 9
#define INC_BUTTON                  10
//================================//


#define INDEX_CELSIUS_LCD           13
#define INDEX_TEMP_LCD              7   
#define INDEX_HUMI_LCD              7
#define INDEX_HOUR_LCD              0
#define INDEX_MIN_LCD               5          
#define INDEX_SEC_LCD               10
#define INDEX_DATE_LCD              0
#define INDEX_MON_LCD               5
#define INDEX_YEAR_LCD              10


#define TIME_VIEW_RTL               1000        //10 000ms
#define TIME_VIEW_SIM               1100        //11 000ms
#define TIME_VIEW_HUMI_TEMP         1000        //10 000ms
#define TIME_TO_READ_RTL            50          //500ms
#define TIME_OUT_ADJUST_TIME        1000        //10 000ms
#define TIME_BLINKING               30         //300ms

void FSM_Init(void);
void FSM_Control(void);

void RTC_GetDateTime(void);


#endif	/* FSM_H */

