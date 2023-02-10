/* 
 * File:   fsm.h
 * Author: DELL
 *
 * Created on February 11, 2023, 12:07 AM
 */

#ifndef FSM_H
#define	FSM_H


#include <p18f4620.h>
#include "lcd.h"
#include "global.h"
#include "i2c_ds1307.h"


//  [DEC]       [MODE]       [INC]
#define DEC_BUTTON                  4
#define MODE_BUTTON                 5
#define INC_BUTTON                  6

#define INDEX_HOUR_LCD              0
#define INDEX_MIN_LCD               3
#define INDEX_SEC_LCD               6
#define INDEX_WEEK_DAY_LCD          0
#define INDEX_DATE_LCD              5
#define INDEX_MONTH_LCD             8
#define INDEX_YEAR_LCD              11

#define TIME_OUT_FOR_ADJUSTMENT     15          //15s
#define TIME_OUT_ALARM_GO_OFF       30          //30s

enum Mode {INIT, NORMAL_DISPLAY, 
            ADJUST_TIME, ADJUST_MIN, ADJUST_HOUR,
            ADJUST_WEEK_DAY, ADJUST_DATE, ADJUST_MONTH, ADJUST_YEAR,
            SET_ALARM, SET_ALARM_HOUR, SET_ALARM_MIN, ALARM_GO_OFF};
            

void FSM_Init(void);
void FSM_AlarmControl(void);

#endif	/* FSM_H */

