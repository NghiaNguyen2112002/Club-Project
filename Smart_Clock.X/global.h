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

#define SCREEN_ALARM_GO_OFF_0                 "                "
#define SCREEN_ALARM_GO_OFF_1                 "                "

//=========CUSTOM LCD=============//
extern unsigned char alarm_1[];
extern unsigned char alarm_2[];
extern unsigned char alarm_3[];
extern unsigned char alarm_4[];
extern unsigned char alarm_5[];
extern unsigned char alarm_6[];

extern unsigned char alarm_ring_1[];
extern unsigned char alarm_ring_2[];
extern unsigned char alarm_ring_3[];
extern unsigned char alarm_ring_4[];
extern unsigned char alarm_ring_5[];
extern unsigned char alarm_ring_6[];

///////////////////////////////////


extern unsigned char _hour, _minute, _second, 
                    _week_day, _date, _month, _year;

extern unsigned char _hourAlarm, _minuteAlarm;
extern unsigned char _flagAlarm;

extern unsigned char _flagBlinkCursor, _flagGetTime, _flagFrameAnimation;

extern unsigned int _counterTimeOut, _counterEvery_ms, _counterFrameAnimation;

#endif	/* GLOBAL_H */

