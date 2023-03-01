#include "adc.h"



void ADC_Init(void){
    TRISA = 0xFF;
    ADCON1 = 0x0B;       //AN0 - AN3 (RA0 - RA3)
    ADCON2 = 0x04;       //FOSC / 4
}



int ADC_Read(unsigned char channel){
    int result;
    ADCON0 = channel << 2;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    result = ADRESH;
    result = (result << 2) + (ADRESL >> 6);
    
    return result;
}
