#include "timer.h"

unsigned int value_timer0 = 0, value_timer1 = 0, value_timer2 = 0, value_timer3 = 0;
unsigned int counter_timer0 = 0, counter_timer1 = 0, counter_timer2 = 0, counter_timer3 = 0;
unsigned int MUL_timer0 = 0, MUL_timer1 = 0, MUL_timer2 = 0, MUL_timer3 = 0;

unsigned char flag_timer0, flag_timer1, flag_timer2, flag_timer3;



void TMR0_Init(unsigned int count){
    T0CONbits.TMR0ON = 0;               //turn off timer0
    value_timer0 = count;
    T0CONbits.T08BIT = 0;               //set 16 bit timer0
    TMR0L = (65535 - value_timer0) % 256;
    TMR0H = (65535 - value_timer0) / 256;
    T0CONbits.T0CS = 0;                 // select internal clock include crystal's
    T0CONbits.PSA = 1;                  //no prescaler
    INTCONbits.T0IE = 1;                //enable timer0 interrupt
    INTCONbits.T0IF = 0;                //clear timer0 interrupt flag
    INTCON2bits.TMR0IP = 1;             //timer0 interrupt high priority
    T0CONbits.TMR0ON = 1;               //start timer 0
    
}

void TMR1_Init(unsigned int count){
    T1CONbits.TMR1ON = 0;               //turn off timer1
    value_timer1 = count;
    TMR1H = (65525 - value_timer1) % 256;
    TMR1L = (65535 - value_timer1) / 256;
    PIE1bits.TMR1IE = 1;                //enable timer1 interrupt
    PIR1bits.TMR1IF = 0;                // clear timer1 interrupt flag
    IPR1bits.TMR1IP = 0;                //timer1 interrupt low priority
//    T1CON
    T1CONbits.RD16 = 1;                 //set 16 bit timer1  
    T1CONbits.T1RUN = 1;
    T1CONbits.T1CKPS0 = 0;              //prescaler 1:1
    T1CONbits.T1CKPS1 = 0;              
    T1CONbits.T1OSCEN = 0;              //oscillator invert and feedback for external oscillator
//    T1CONbits.T1SYNC = 0;               //this bit is ignored when TMR1CS = 0
    T1CONbits.TMR1CS = 0;               //internal clock
    T1CONbits.TMR1ON = 1;               //start timer1
    
}

void TMR2_Init(unsigned char count){
    T2CONbits.TMR2ON = 0;               //turn off timer2
    TMR2 = 0x00;
    value_timer2 = count;
    PR2 = value_timer2;
    PIE1bits.TMR2IE = 1;                //enable timer2 interrupt
    PIR1bits.TMR2IF = 0;                //clear timer2 interrupt flag
    IPR1bits.TMR2IP = 0;                //timer2 interrupt low priority
    	
    T2CONbits.T2CKPS0 = 0;              //
	T2CONbits.T2CKPS1 = 0;              // prescaler 1:1
	T2CONbits.TMR2ON = 1;               // start timer2
    
}
void TMR3_Init(unsigned int count){
	T3CONbits.TMR3ON = 0;			// turn off timer 3
	value_timer3 = count;
	TMR3H = ((65535-value_timer3)/256);	// count timer3_value times
	TMR3L = ((65535-value_timer3)%256);	//
	PIE2bits.TMR3IE = 1;			// enable timer3 interrupt
	PIR2bits.TMR3IF = 0;			// clear timer3 interrupt flag

	IPR2bits.TMR3IP = 0;			// timer3 interrupt low priority 	

	//T1CON
	T3CONbits.RD16 = 1;				// select timer3 16 bits mode
	T3CONbits.T3CKPS0 = 0;			//
	T3CONbits.T3CKPS1 = 0;			// prescaler 1:1
//	T3CONbits.T3SYNC = 0;			// this bit ignore when TMR3CS = 0
	T3CONbits.TMR3CS = 0;			// select internal clock source
	T3CONbits.TMR3ON = 1;	
    
}

void TMR0_Start(void){
    TMR0L = (65535 - value_timer0) % 256;
    TMR0H = (65535 - value_timer0) / 256;
    T0CONbits.TMR0ON = 1;               //start timer 0
        
}

void TMR1_Start(void){
    TMR1H = (65525 - value_timer1) % 256;
    TMR1L = (65535 - value_timer1) / 256;
    T1CONbits.TMR1ON = 1;               //start timer1

}
void TMR2_Start(void){
    PR2 = value_timer2;
	T2CONbits.TMR2ON = 1;               // start timer2

}
void TMR3_Start(void){
    TMR3L = (65535 - value_timer3) % 256;
    TMR3H = (65535 - value_timer3) / 256;
    T3CONbits.TMR3ON = 1;               //start timer3
    
}   


void TMR0_Stop(void){
    T0CONbits.TMR0ON = 0;
}

void TMR1_Stop(void){
    T1CONbits.TMR1ON = 0;
}

void TMR2_Stop(void){
    T2CONbits.TMR2ON = 0;
}

void TMR3_Stop(void){
    T3CONbits.TMR3ON = 0;
}

void TMR0_Isr(void){
    counter_timer0++;
    if(counter_timer0 >= MUL_timer0){
        counter_timer0 = 0;
        flag_timer0 = 1;
    }
}

void TMR1_Isr(void){
    counter_timer1++;
    if(counter_timer1 >= MUL_timer1){
        counter_timer1 = 0;
        flag_timer1 = 1;
    }
}

void TMR2_Isr(void){
    counter_timer2++;
    if(counter_timer2 >= MUL_timer2){
        counter_timer2 = 0;
        flag_timer2 = 1;
    }
}
void TMR3_Isr(void){
    counter_timer3++;
    if(counter_timer3 >= MUL_timer3){
        counter_timer3 = 0;
        flag_timer3 = 1;
    }  
}

void TMR0_SetTime_ms(unsigned int time){
    MUL_timer0 = time;                      //timer0 1ms
    counter_timer0 = 0;
    flag_timer0 = 0;
}
void TMR1_SetTime_ms(unsigned int time){
    MUL_timer1 = time / 2;                 //timer1 2ms
    counter_timer1 = 0;
    flag_timer1 = 0; 
}
void TMR2_SetTime_ms(unsigned int time){
    MUL_timer2 = time;                      //timer2 1ms
    counter_timer2 = 0;
    flag_timer2 = 0;    
}
void TMR3_SetTime_ms(unsigned int time){
    MUL_timer3 = time / 10;                  //timer3 10ms
    counter_timer3 = 0;
    flag_timer3 = 0;
}