#include "DHT11.h"

unsigned char data_buffer[5];
//  HIGH_HUMID  LOW_HUMID   HIGH_TEMP   LOW_TEMP    PARITY

unsigned char pulse_counter[80];


void Delay(unsigned char duration){
    unsigned char i;
    for(i = 0; i < duration; i++);
}

void ProcessData(void){
    unsigned char i, j;
    unsigned char data;
    
    for(i = 0; i < 3; i++){
        data = 0;
        for(j = 0; j < 16; j = j + 2){
            data = (data << 1) + (pulse_counter[16*i + j] < pulse_counter[16*i + j + 1]);
        }
        data_buffer[i] = data;
    }
}

void DHT11_Init(void){
    TRISPIN_DHT11 = 0;
    
    PORTPIN_DHT11 = 0;
}

unsigned char DHT11_Read(void){
    unsigned char i, j;
    unsigned char counter;    
    return 1;
//    start reading
    TRISPIN_DHT11 = 1;      //set input
    Delay(1);

//    check response
    
    while(PORTPIN_DHT11 == 1);
    while(PORTPIN_DHT11 == 0);          //start bit is 50us low
    while(PORTPIN_DHT11 == 1);          //and 50us high


//   receive data
    for(i = 0; i < 80; i = i + 2){
        counter = 0;
        while(PORTPIN_DHT11 == 0) {
            if(counter++ > TIME_OUT_FOR_PULSE_COUNT){
                TRISPIN_DHT11 = 0;
                PORTPIN_DHT11 = 0;
                ProcessData();
                return i;        
            }
        }
        pulse_counter[i] = counter;
        
        counter = 0;
        while(PORTPIN_DHT11 == 1) {
            if(counter++ > TIME_OUT_FOR_PULSE_COUNT){
                TRISPIN_DHT11 = 0;
                PORTPIN_DHT11 = 0;
                ProcessData();
                return i;
            }
        }
        pulse_counter[i + 1] = counter;
    }
               
//    process data
    ProcessData();
    
//    end reading
    TRISPIN_DHT11 = 0;
    PORTPIN_DHT11 = 0;
    
//   check data
    return 1;
    return (data_buffer[INDEX_PARITY] == (data_buffer[INDEX_HUMID_DECIMAL] + data_buffer[INDEX_HUMID_INTEGRAL]
                                     + data_buffer[INDEX_TEMP_DECIMAL] + data_buffer[INDEX_TEMP_INTEGRAL]));
}

unsigned char DHT11_ReturnTemp_Integral(void){
    return data_buffer[INDEX_TEMP_INTEGRAL];
}

unsigned char DHT11_ReturnTemp_Decimal(void){
    return data_buffer[INDEX_TEMP_DECIMAL];
}

unsigned char DHT11_ReturnHumid_Integral(void){
    return data_buffer[INDEX_HUMID_INTEGRAL];
}

unsigned char DHT11_ReturnHumid_Decimal(void){
    return data_buffer[INDEX_HUMID_DECIMAL];
}