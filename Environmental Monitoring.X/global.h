/* 
 * File:   global.h
 * Author: DELL
 *
 * Created on February 15, 2023, 8:40 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#define SCREEN_NORMAL_DISPLAY_0               "  :  :  "       //  "18:13:50"  
#define SCREEN_NORMAL_DISPLAY_1               "  /  /  "       //  "30/08/23"

#define SCREEN_DATA_DISPLAY_0                 " T:    C"       //  " T: 30*C"        
#define SCREEN_DATA_DISPLAY_1                 " H:   % "       //  " H: 50% "


extern unsigned char _hour, _minute, _second,   
                    _week_day, _date, _month, _year;


extern unsigned char _flag_get_time, _flag_blinking;
extern unsigned int _counter_display_time, _counter_time_out, 
                    _counter_blinking, _counter_reading_data;


#endif	/* GLOBAL_H */

