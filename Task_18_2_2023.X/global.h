/* 
 * File:   global.h
 * Author: DELL
 *
 * Created on February 11, 2023, 12:07 AM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#include <p18f4620.h>


#define SCREEN_TEMP_HUMID_0               "TEMP :        C"       
#define SCREEN_TEMP_HUMID_1               "HUMI :       % "        
    
#define SCREEN_TIME_0                     "   /    /      "
#define SCREEN_TIME_1                     "   /    /      "  

#define SCREEN_SIM_0                      "  SIM          "
#define SCREEN_SIM_1                      "               "


extern unsigned char _hour, _minute, _second, 
                    _date, _month, _year;

extern unsigned int _temp, _humid;

extern unsigned int _time_change_screen, _time_to_read_RTL, 
                    _timeout, _time_blinking;

#endif	/* GLOBAL_H */

