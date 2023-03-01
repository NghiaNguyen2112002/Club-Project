#include "interrupt.h"


void INT_Init(void){
    INTCONbits.GIE = 1;         //enable interrupt
    RCONbits.IPEN = 1;          //enable interrupt priority
    INTCONbits.PEIE = 1;        //Peripheral External Interupt Enable
}


#pragma code InterruptVectorLow		= 0x18
void InterruptVectorLow(void)
{
	_asm
		GOTO	low_isr
	_endasm
}

#pragma code InterruptVectorHigh 	= 0x08
void InterruptVectorHigh(void)
{
	_asm
		GOTO	high_isr
	_endasm
}

#pragma code
#pragma interruptlow	low_isr
void low_isr(void)
{
	if (INTCONbits.T0IF) // timer0
	{
		TMR0_Stop();
		INTCONbits.T0IF = 0;
		TMR0_Start();
		TMR0_Isr();
	}

	if (PIR1bits.TMR1IF) // timer1
	{
		TMR1_Stop();
		PIR1bits.TMR1IF = 0;
		TMR1_Start();	
		TMR1_Isr();
	}

	

	if (PIR2bits.TMR3IF) // timer3
	{
		TMR3_Stop();
		PIR2bits.TMR3IF = 0;
		TMR3_Start();
		TMR3_Isr();
	}

	if (INTCONbits.INT0IF) // ext_interupt0
	{
		INTCONbits.INT0IF = 0;
		//add code here
	}

        if(PIR1bits.RCIF == 1) // UART interupt Receive
	{
		PIR1bits.RCIF = 0;
	}
}

#pragma code
#pragma interrupt		high_isr
void high_isr(void)
{
	if (INTCONbits.T0IF) // timer0
	{
		TMR0_Stop();
		INTCONbits.T0IF = 0;
		TMR0_Start();
		TMR0_Isr();
	}

	if (PIR1bits.TMR1IF) // timer1
	{
		TMR1_Stop();
		PIR1bits.TMR1IF = 0;
		TMR1_Start();	
		TMR1_Isr();
	}

	

	if (PIR2bits.TMR3IF) // timer3
	{
		TMR3_Stop();
		PIR2bits.TMR3IF = 0;
		TMR3_Start();
		TMR3_Isr();
	}

	if (INTCONbits.INT0IF) // ext_interupt0
	{
		INTCONbits.INT0IF = 0;
		//add code here
	}

        if(PIR1bits.RCIF == 1) // UART interupt Receive
	{
		PIR1bits.RCIF = 0;
	}

        //if(PIR1bits.TXIF == 1) // UART interupt Receive
}

