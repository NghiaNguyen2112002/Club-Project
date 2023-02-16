/* 
 * File:   i2c.h
 * Author: DELL
 *
 * Created on February 9, 2023, 8:18 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <p18f4620.h>

#define TRIS_SCL                TRISCbits.RC3
#define TRIS_SDA                TRISCbits.RC4

#define I2C_CLOCK               100             //100kHz
#define F_CRYSTAL               20000           //20 Mhz

#define DS1307_WRITE_MODE       0xD0
#define DS1307_READ_MODE        0xD1     


#define ADDRESS_SECOND          0x00
#define ADDRESS_MINUTE          0x01
#define ADDRESS_HOUR            0x02
#define ADDRESS_WEEK_DAY        0x03
#define ADDRESS_DATE            0x04
#define ADDRESS_MONTH           0x05
#define ADDRESS_YEAR            0x06

#define ADDRESS_FIRST_PROGRAM   0x25
#define ADDRESS_HOUR_ALARM      0x26
#define ADDRESS_MIN_ALARM       0x27
#define ADDRESS_FLAG_ALARM      0x28
 

void I2C_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(unsigned char byte);

unsigned char I2C_Read(void);

void I2C_WriteDS1307(unsigned char address, unsigned char data);
unsigned char I2C_ReadDS1307(unsigned char address);

#endif	/* I2C_H */

