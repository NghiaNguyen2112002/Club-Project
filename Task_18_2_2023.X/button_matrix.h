/* 
 * File:   button.h
 * Author: DELL
 *
 * Created on February 8, 2023, 12:36 PM
 */

#ifndef BUTTON_MATRIX_H
#define	BUTTON_MATRIX_H

#include <p18f4620.h>

#define TRIS_BUTTON                         TRISC
#define PORT_BUTTON                         PORTC

#define MAX_ROW                             4
#define MAX_COL                             4
#define NO_OF_BUTTONS                       16
#define DURATION_FOR_AUTO_INCREASING        200   //10s

#define BUTTON_IS_PRESSED                   0
#define BUTTON_IS_RELEASED                  1


void KEY_Init(void);
void KEY_Reading(void);

unsigned char KEY_IsStuck(unsigned char index);
unsigned char KEY_IsPressed(unsigned char index);
unsigned char KEY_IsPressed_ms(unsigned char index, unsigned int duration);

#endif	/* BUTTON_H */

