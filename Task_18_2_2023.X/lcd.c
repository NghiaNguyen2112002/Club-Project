#include "lcd.h"


int current_row, current_col;
unsigned char LcdScreen[2][16] = {
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

void LCD_Delay(unsigned char duration){
    unsigned int i;
    for(i = 0; i < duration; i++);
}

void Delay_virtual(unsigned char duration){
    unsigned int i, j;
    for(i = 0; i < duration; i++)
        for(j = 0; j < 250; j++);
}

void LCD_Write4bits(unsigned char data){
    LCD_DATA_OUT(data);
    EN(SET);
    LCD_Delay(1);
    EN(CLR);
    LCD_Delay(1);
}

void LCD_WriteData(unsigned char data){
    RS(DAT);
    Delay_virtual(1);
    LCD_Write4bits(data);
    LCD_Write4bits(data << 4);
    RS(CMD);
}

void LCD_WriteCommand(unsigned char cmd){
    RS(CMD);
    Delay_virtual(1);
    LCD_Write4bits(cmd);
    LCD_Write4bits(cmd << 4);
    RS(CMD);
}

void LCD_SendCommand(unsigned char cmd){
    LCD_PORT &= 0x0F;
    LCD_PORT |= (cmd & 0xF0);
    
    LCD_PORT |= 1 << LCD_E;
    Delay_virtual(1);
    LCD_PORT &= ~ (1 << LCD_E);
    Delay_virtual(1);

    LCD_PORT &= 0x0F;
    LCD_PORT |= cmd << 4;
    
    LCD_PORT |= (1 << LCD_E);
    Delay_virtual(1);
    LCD_PORT &= ~ (1 << LCD_E);
    
    Delay_virtual(1);
    
}

void LCD_Init(void){

    unsigned char cmd;
    
    LCD_TRIS = 0x00;
    
    Delay_virtual(250);              //wait until Vcc = 4.5V
    
    LCD_PORT &= 0x0F;
    LCD_PORT &= 0xF8;           //enable LCD
    
//--------ONE----------
    LCD_DATA_OUT(0x03 << 4);
    EN(SET);
    Delay_virtual(1);
    EN(CLR);
    Delay_virtual(1);
    
//--------TWO----------
    LCD_DATA_OUT(0x03 << 4);
    EN(SET);
    Delay_virtual(1);
    EN(CLR);
    Delay_virtual(1);
    
//--------THREE----------
    LCD_DATA_OUT(0x03 << 4);
    EN(SET);
    Delay_virtual(1);
    EN(CLR);
    Delay_virtual(1);

//--------FOUR----------
    LCD_DATA_OUT(0x02 << 4);
    EN(SET);
    Delay_virtual(1);
    EN(CLR);
    Delay_virtual(1);

//   LCD is already set to 4 bit mode
    
    LCD_SendCommand(0x28);              //2 line + 5x8 dot
    LCD_SendCommand(0x0C);              //increment address + invisible cursor shift
}

void LCD_SetCursor(unsigned char row, unsigned char col){
    switch(row){
        case 0:
            LCD_WriteCommand(0x80 + col);
            break;
        case 1:
            LCD_WriteCommand(0xC0 + col);
            break;       
    }
}

void LCD_ClearBuffer(void){
    unsigned char i, j;
    for(i = 0; i < 2; i++){
        for(j = 0; j < 16; j++){
            LcdScreen[i][j] = ' ';
        }
    }
}

void LCD_UpdateCharBuffer(unsigned char c){
    LcdScreen[current_row][current_col] = c;
    current_col++;
}

void LCD_PrintCharBuffer(unsigned char x, unsigned char y, unsigned char c){
    current_row = x % 2;
    current_col = y % 16;
    LcdScreen[current_row][current_col] = c;
}


void LCD_PrintNumBuffer(unsigned char x, unsigned char y, long num){
    char flag_num = 0;
    unsigned char i;
    unsigned long power_of_10 = 1000;
    current_row = x % 2;
    current_col = y % 16;
    
    if(num < 0) {
        num *= -1;
        LCD_UpdateCharBuffer('-');
    }
    else if(num == 0){
        LCD_UpdateCharBuffer(' ');
        LCD_UpdateCharBuffer(' ');
        LCD_UpdateCharBuffer(' ');
        LCD_UpdateCharBuffer('0');
        return;
    }
    
    
    for(i = 4; i > 0; i--){
        if( (num / power_of_10) != 0){
            flag_num = 1;
            LCD_UpdateCharBuffer(num / power_of_10 + '0');
        }
        else{
            if(flag_num != 0) LCD_UpdateCharBuffer('0');
            else LCD_UpdateCharBuffer(' ');
        }
        num %= power_of_10;
        power_of_10 /= 10;
    }


}

void LCD_PrintStringBuffer(unsigned char x, unsigned char y, const rom unsigned char* str){
    current_row = x % 2;
    current_col = y % 16;
    
    while(*str){
        LCD_UpdateCharBuffer(* str++);
    }
}

void LCD_PrintStringBufferL(unsigned char x, unsigned char y, const rom unsigned char* str, unsigned char length){
    unsigned char i;
    current_row = x % 2;
    current_col = y % 16;
    for(i = 0; i < length; i++) LCD_UpdateCharBuffer(str[i]);
}
void LCD_DisplayScreen(void){
    unsigned char i;
    
    LCD_SetCursor(0, 0);
    for(i = 0; i < 16; i++){
        LCD_WriteData(LcdScreen[0][i]);
    }
    
    LCD_SetCursor(1, 0);
    for(i = 0; i < 16; i++){
        LCD_WriteData(LcdScreen[1][i]);
    }
}



void LCD_PrintTimeBuffer(unsigned char x, unsigned char y, unsigned char time){
    current_row = x % 2;
    current_col = y % 16;
    
    LCD_UpdateCharBuffer(time / 10 + '0');
    LCD_UpdateCharBuffer(time % 10 + '0');
}

void LCD_CreateChar(unsigned char index, unsigned char* icon){
    unsigned char i;
    LCD_WriteCommand(0x40 + 8*index);
    
    for(i = 0; i < 8; i++){
        LCD_WriteData(icon[i]);
    }
}