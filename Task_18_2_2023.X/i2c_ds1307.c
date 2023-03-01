#include "i2c_ds1307.h"

unsigned char ack_bit; 
//=========sub function for DS1307===========
unsigned char BCD_To_DEC(unsigned char BCD){
    unsigned char low, high;
    low = BCD & 0x0F;
    high = (BCD >> 4) * 10;
    return (low + high);
}

unsigned char DEC_To_BCD(unsigned char DEC){
    unsigned char low, high;
    low = DEC % 10;
    high = (DEC / 10) << 4;
    return low + high ;
}
//=========end subfunction for DS1307===========

void I2C_Init(void){
//    set clk_pin + sda_pin input
    TRIS_SCL = 1;
    TRIS_SDA = 1;
    
    SSPSTATbits.SMP = 0;        
    SSPSTATbits.CKE = 0;        
    
    SSPCON1bits.SSPEN = 1;      //enables the serial port and configures the SDA 
                                //and SCL pins as the serial port pins
    SSPCON1bits.SSPM3 = 1;      //I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
    SSPCON1bits.SSPM2 = 0;      //
    SSPCON1bits.SSPM1 = 0;      //
    SSPCON1bits.SSPM0 = 0;      //
    
//   baudrate = 100kHz (f = 20Mhz)
    SSPADD = 49;            
}

void I2C_Start(void){
    PIR1bits.SSPIF = 0;             //clear ssp interrupt bit
    SSPCON2bits.SEN = 1;            //send start bit
    while(!PIR1bits.SSPIF);         //wait for interrupt flag to go high indicating transmission is complete
}

void I2C_Stop(void){
    PIR1bits.SSPIF = 0;
    SSPCON2bits.PEN = 1;
    while(!PIR1bits.SSPIF);         //wait for interrupt flag to go high indicating transmission is complete
}

void I2C_Write(unsigned char byte){
    PIR1bits.SSPIF = 0;
    SSPBUF = byte;
    while(!PIR1bits.SSPIF);
}

unsigned char I2C_Read(void){
    PIR1bits.SSPIF = 0;
    SSPCON2bits.RCEN = 1;          //Enables Receive mode for I2C 
    while(!PIR1bits.SSPIF);
    return (SSPBUF);
}

void I2C_WriteDS1307(unsigned char address, unsigned char data){
    I2C_Start();
    
    I2C_Write(DS1307_WRITE_MODE);
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    I2C_Write(address);
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    I2C_Write(DEC_To_BCD(data));
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    I2C_Stop();
}

unsigned char I2C_ReadDS1307(unsigned char address){
    unsigned char data;

    I2C_Start();
     
    I2C_Write(DS1307_WRITE_MODE);
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    I2C_Write(address);
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    I2C_Start();

    I2C_Write(DS1307_READ_MODE);
    ack_bit = 1;
    while(ack_bit) ack_bit = SSPCON2bits.ACKSTAT;
    
    data = I2C_Read();

    return BCD_To_DEC(data);
}

