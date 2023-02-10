/* 
 * File:   global.h
 * Author: DELL
 *
 * Created on February 11, 2023, 12:07 AM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#include <p18f4620.h>


#define SCREEN_NORMAL_DISPLAY_0               "  :  :          "        //18:13: 50
#define SCREEN_NORMAL_DISPLAY_1               "       /  /     "        //THU 30/08/2023
    
#define SCREEN_TURN_ALARM_0                   "   TURN ALARM:  "
#define SCREEN_TURN_ALARM_1                   " <ON>     <OFF> "

#define SCREEN_SET_ALARM_0                    "   SET  ALARM   "  
#define SCREEN_SET_ALARM_1                    "H:      M:      "

#define SCREEN_ALARM_GO_OFF_0                 "RINGGGG RINGGGGG"
#define SCREEN_ALARM_GO_OFF_1                 "RENGGGGG RENGGGG"

extern unsigned char _hour, _minute, _second, 
                    _week_day, _date, _month, _year;

extern unsigned char _hourAlarm, _minuteAlarm;
extern unsigned char _flagAlarm;

extern unsigned char _flagEverySec, _flagBlinkCursor, _flagGetTime;

extern unsigned char _counterTimeOut, _counterEvery_ms;

#endif	/* GLOBAL_H */

