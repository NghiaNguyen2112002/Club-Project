/* 
 * File:   fsm.h
 * Author: DELL
 *
 * Created on February 8, 2023, 10:07 PM
 */

#ifndef FSM_H
#define	FSM_H

#include <p18f4620.h>
#include "lcd.h"
#include "output.h"
#include "global.h"


//press 1s MODE_BUTTON to enter adjustment mode
#define INC_BUTTON              4
#define MODE_BUTTON             5
#define DEC_BUTTON              6

#define RED_1_BUTTON            8
#define YELLOW_1_BUTTON         9
#define GREEN_1_BUTTON          10
#define RED_2_BUTTON            12
#define YELLOW_2_BUTTON         13
#define GREEN_2_BUTTON          14

enum MODE {INIT, MANUAL, START_AUTO, STOP_AUTO,
            MANUAL_RED_1, MANUAL_GREEN_1, MANUAL_YELLOW_1,
            MANUAL_RED_2, MANUAL_GREEN_2, MANUAL_YELLOW_2,
            AUTO_RED_GREEN, AUTO_RED_YELLOW, AUTO_GREEN_RED, AUTO_YELLOW_RED,
            ADJUST, ADJUST_GREEN, ADJUDT_YELLOW};


void FSM_Init(void);   
void FSM_TrafficLight(void);

#endif	/* FSM_H */

