/* 
 * File:   lcd.h
 * Author: DELL
 *
 * Created on February 7, 2023, 3:27 PM
 */

#ifndef LCD_H
#define	LCD_H

#include <p18f4620.h>

#define LCD_RS                      2
//#define LCD_RW
#define LCD_E                       3
#define LCD_D4                      4
#define LCD_D5                      5
#define LCD_D6                      6
#define LCD_D7                      7

#define LCD_LINE0                   0x00
#define LCD_LINE1                   0x40

#define CLR                         0
#define SET                         1
#define DAT                         1	// data mode
#define CMD                         0	// command mode
#define READ                        1
#define WRITE                       0

#define LCD_PORT                    PORTB
#define LCD_TRIS                    TRISB

//4 bit msb lcd control
#define RS(x)                       ( (x) ? (LCD_PORT |= 1 << LCD_RS) : (LCD_PORT &= ~(1 << LCD_RS)) )
#define EN(x)                       ( (x) ? (LCD_PORT |= 1 << LCD_E) : (LCD_PORT &= ~(1 << LCD_E)) )

#define LCD_DATA_OUT(x)             LCD_PORT &= 0x0F; LCD_PORT |= (x);
#define LCD_DATA_IN                 LCD_PORT & 0x0F;
#define LCD_DIR_IN                  LCD_PORT |= 0x0F;

void LCD_Init(void);
void LCD_ClearBuffer(void);
void LCD_PrintCharBuffer(unsigned char x, unsigned char y, unsigned char c);
void LCD_PrintNumBuffer(unsigned char x, unsigned char y, long num);
void LCD_PrintStringBuffer(unsigned char x, unsigned char y, const rom unsigned char* str);
void LCD_PrintStringBufferL(unsigned char x, unsigned char y, const rom unsigned char* str, unsigned char length);

void LCD_DisplayScreen(void);



#endif	/* LCD_H */

