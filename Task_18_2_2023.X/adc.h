/* 
 * File:   adc.h
 * Author: DELL
 *
 * Created on February 23, 2023, 10:00 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <p18f4620.h>

#define CHANNEL             13         

void ADC_Init(void);
int ADC_Read(unsigned char channel);

#endif	/* ADC_H */

