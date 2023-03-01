#include "global.h"


unsigned char _hour = 0, _minute = 0, _second = 0,
               _week_day = 0, _date = 0, _month = 0, _year = 0;

unsigned char _flag_get_time = 0, _flag_blinking = 0;

unsigned int _counter_display_time = 0, _counter_time_out = 0,
            _counter_blinking = 0, _counter_reading_data = 0;