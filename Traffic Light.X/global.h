/* 
 * File:   global.h
 * Author: DELL
 *
 * Created on February 8, 2023, 10:42 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#define SCREEN_MANUAL_0                 "                "
#define SCREEN_MANUAL_1                 " ____MANUAL____ "

#define SCREEN_MANUAL_RED_1             "RED 1  "
#define SCREEN_MANUAL_RED_2             "RED 2  "
#define SCREEN_MANUAL_GREEN_1           "GREEN 1"
#define SCREEN_MANUAL_GREEN_2           "GREEN 2"
#define SCREEN_MAUAL_YELLOW_1           "YELLOW1"
#define SCREEN_MANUAL_YELLOW_2          "YELLOW2"

#define SCREEN_ADJUST_0                 "  CHOOSE LIGHT  "
#define SCREEN_ADJUST_1                 "GREEN     YELLOW"

#define SCREEN_ADJUST_GREEN_0           "   AJUST MODE   "
#define SCREEN_ADJUST_GREEN_1           "GREEN:          "
#define SCREEN_ADJUST_YELLOW_0          "    AJUST MODE  "
#define SCREEN_ADJUST_YELLOW_1          "YELLOW:         "

#define SCREEN_AUTO_RED_1               "1RED    "
#define SCREEN_AUTO_RED_2               "2RED    "
#define SCREEN_AUTO_GREEN_1             "1GREEN  "
#define SCREEN_AUTO_GREEN_2             "2GREEN  "
#define SCREEN_AUTO_YELLOW_1            "1YELLOW "
#define SCREEN_AUTO_YELLOW_2            "2YELLOW "

extern unsigned int _timeRed, _timeGreen, _timeYellow;
extern unsigned int _counterLight_1, _counterLight_2;
extern unsigned int _timeOutAjustMode;

extern unsigned char _flagEvery1Sec;
#endif	/* GLOBAL_H */

