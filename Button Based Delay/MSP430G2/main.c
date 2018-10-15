#include <msp430.h> 

// Button Delay for G2

volatile unsigned int i = 2000;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1SEL = 0;					// selecting GPIO
	P1DIR |= BIT6;              // setting P1.6 to 1
	P1DIR &= ~(BIT3);           // setting P1.3 input
    P1REN |= BIT3;				// enable port 1 resister
	P1OUT |= BIT3;				// choosing pull-up resistor
	P1IE  |= BIT3;    			// setting P1.3 as an interrupt pin, will triggered whenever the pin is changed 
	P1IES |=BIT3;				// setting as falling edge
    P1IFG &=~(BIT3);			// clearing interrupt flag

    _BIS_SR(LPM4_bits + GIE);	//enter LPM4 mode and enable global interrupt
}
 
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)	// will execute code once interrupt is triggered
{   
	P1OUT ^= BIT1; 				// changing states of P1.1
    do (i--);
    while (i != 0);
    P1IFG &=~(BIT3); 			// clears interrupt flag
}
