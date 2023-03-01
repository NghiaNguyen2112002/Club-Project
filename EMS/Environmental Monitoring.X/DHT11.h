/* 
 * File:   DHT11.h
 * Author: DELL
 *
 * Created on February 15, 2023, 7:23 PM
 */

#ifndef DHT11_H
#define	DHT11_H


#include <p18f4620.h>
#include "lcd.h"


#define TRISPIN_DHT11                   TRISAbits.RA4
#define PORTPIN_DHT11                   PORTAbits.RA4

#define INDEX_HUMID_INTEGRAL            0
#define INDEX_HUMID_DECIMAL             1
#define INDEX_TEMP_INTEGRAL             2
#define INDEX_TEMP_DECIMAL              3
#define INDEX_PARITY                    4

#define TIME_OUT_FOR_PULSE_COUNT        100

#define ERROR_DHT11_FAIL_READING        0

void DHT11_Init(void);

unsigned char DHT11_Read(void);

unsigned char DHT11_ReturnTemp_Integral(void);
unsigned char DHT11_ReturnTemp_Decimal(void);
unsigned char DHT11_ReturnHumid_Integral(void);
unsigned char DHT11_ReturnHumid_Decimal(void);

#endif	/* DHT11_H */

