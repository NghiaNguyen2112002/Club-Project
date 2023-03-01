/* 
 * File:   timer.h
 * Author: DELL
 *
 * Created on February 7, 2023, 1:05 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#include <p18f4620.h>


void TMR0_Init(unsigned int count);
void TMR1_Init(unsigned int count);
void TMR2_Init(unsigned char count);
void TMR3_Init(unsigned int count);

void TMR0_Start(void);
void TMR1_Start(void);
void TMR2_Start(void);
void TMR3_Start(void);

void TMR0_Stop(void);
void TMR1_Stop(void);
void TMR2_Stop(void);
void TMR3_Stop(void);

void TMR0_Isr(void);
void TMR1_Isr(void);
void TMR2_Isr(void);
void TMR3_Isr(void);

void TMR0_SetTime_ms(unsigned int time);
void TMR1_SetTime_ms(unsigned int time);
void TMR2_SetTime_ms(unsigned int time);
void TMR3_SetTime_ms(unsigned int time);


extern unsigned char flag_timer0, flag_timer1, flag_timer2, flag_timer3;

#endif	/* TIMER_H */

