/* 
 * File:   interrupt.h
 * Author: DELL
 *
 * Created on February 7, 2023, 2:54 PM
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#include <p18f4620.h>
#include "timer.h"

void INT_Init(void);
void low_isr(void);
void high_isr(void);

#endif	/* INTERRUPT_H */

