/* 
 * File:   output.h
 * Author: DELL
 *
 * Created on February 8, 2023, 7:58 PM
 */

#ifndef OUTPUT_H
#define	OUTPUT_H

#include <p18f4620.h>

#define TRIS_LIGHT                  TRISA

#define LIGHT1_A_TRIS               TRISAbits.RA2
#define LIGHT1_B_TRIS               TRISAbits.RA3

#define LIGHT2_A_TRIS               TRISAbits.RA4
#define LIGHT2_B_TRIS               TRISAbits.RA5

#define LIGHT1_A_PIN               PORTAbits.RA2
#define LIGHT1_B_PIN             PORTAbits.RA3

#define LIGHT2_A_PIN                PORTAbits.RA4
#define LIGHT2_B_PIN                PORTAbits.RA5

void OUT_Init(void);

void OUT_OnRed_1(void);
void OUT_OnYellow_1(void);
void OUT_OnGreen_1(void);

void OUT_OnRed_2(void);
void OUT_OnYellow_2(void);
void OUT_OnGreen_2(void);
#endif	/* OUTPUT_H */

