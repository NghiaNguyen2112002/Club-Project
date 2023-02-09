#include "button_matrix.h"

unsigned char ButtonBuffer[NO_OF_BUTTONS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char MaskOutputOfButton[4] = {0x10, 0x20, 0x40, 0x80};
unsigned char MaskInputOfButton[4] = {0x01, 0x02, 0x04, 0x08};

static unsigned char DebounceButtonBuffer1[NO_OF_BUTTONS];
static unsigned char DebounceButtonBuffer2[NO_OF_BUTTONS];

static unsigned char FlagForButtonPress[NO_OF_BUTTONS];
static unsigned int CounterForButtonPress[NO_OF_BUTTONS];

void KEY_Init(void){
    TRIS_BUTTON = 0x0F;
    PORT_BUTTON = 0xFF;
}

void KEY_Reading(void){
    unsigned char i, j, index;
    for(i = 0; i < MAX_ROW; i++){
        PORT_BUTTON = ~MaskOutputOfButton[i];
        for(j = 0; j < MAX_COL; j++){
            index = i * MAX_ROW + j;
            DebounceButtonBuffer2[index] = DebounceButtonBuffer1[index];
            DebounceButtonBuffer1[index] = PORT_BUTTON & MaskInputOfButton[j];
            
            if(DebounceButtonBuffer1[index] == DebounceButtonBuffer2[index]){
                ButtonBuffer[index] = DebounceButtonBuffer1[index];
                
                if(ButtonBuffer[index] == BUTTON_IS_PRESSED){
                    if(CounterForButtonPress[index] < DURATION_FOR_AUTO_INCREASING){
                        CounterForButtonPress[index]++;
                    }
                }
                else {
                    FlagForButtonPress[index] =  (CounterForButtonPress[index] > 0)
                                                && (CounterForButtonPress[index] < 50);
                    CounterForButtonPress[index] = 0;
                }
            }
        }
    }
}

unsigned char KEY_IsStuck(unsigned char index){
    if(index > NO_OF_BUTTONS) return 0;
    return CounterForButtonPress[index];
}
unsigned char KEY_IsPressed(unsigned char index){
    unsigned char result;
    
    if(index > NO_OF_BUTTONS) return 0;

    result = FlagForButtonPress[index];
    FlagForButtonPress[index] = 0;
    return result;
}
unsigned char KEY_IsPressed_ms(unsigned char index, unsigned int duration){
    if(index >= NO_OF_BUTTONS) return 0;
    return CounterForButtonPress[index] >  duration / 10;       //button is scaned every 10ms
}