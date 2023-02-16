/* 
 * File:   fsm.h
 * Author: DELL
 *
 * Created on February 15, 2023, 8:52 PM
 */

#ifndef FSM_H
#define	FSM_H

#include <p18f4620.h>
#include "global.h"
#include "button_matrix.h"
#include "i2c_ds1307.h"
#include "DHT11.h"

//  [DEC]       [MODE]       [INC]
#define DEC_BUTTON                  4
#define MODE_BUTTON                 5
#define INC_BUTTON                  6

#define INDEX_HOUR_LCD              0
#define INDEX_MIN_LCD               3
#define INDEX_SEC_LCD               6

#define INDEX_DATE_LCD              0
#define INDEX_MONTH_LCD             3
#define INDEX_YEAR_LCD              6

#define INDEX_CELSIUS_SIGN_LCD      14
#define INDEX_TEMP_LCD              12
#define INDEX_HUMID_LCD             12

//every time defined is 10ms reference
#define TIME_DISPLAY_TIME           50               //500ms
#define TIME_BLINKING               30               //300ms
#define TIME_OUT_FOR_ADJUSTMENT     1500             //15s
#define TIME_READING_DATA           100              //1s
 
enum ModeClockControl   {INIT, NORMAL_DISPLAY, 
                        ADJUST_TIME, ADJUST_MIN, ADJUST_HOUR,
                        ADJUST_DATE, ADJUST_MONTH, ADJUST_YEAR};
            
enum ModeDataControl    {INIT_, DISPLAY_DATA, SEND_DATA};     
            
void FSM_Init(void);

void FSM_ClockControl(void);
void FSM_DataControl(void);

#endif	/* FSM_H */

