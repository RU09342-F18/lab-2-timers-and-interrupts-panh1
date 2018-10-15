#include <msp430.h> 

// Button Delay for 5529

volatile unsigned int i = 2000;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1SEL = 0;					// selecting GPIO
	P4DIR |= BIT7;              // setting P4.7 to 1
	P1DIR &= ~(BIT1);           // setting P1.1 input
    P1REN |= BIT1;				// enable port 1 resister
	P1OUT |= BIT1;				// choosing pull-up resistor
	P1IE  |= BIT1;    			// setting P1.1 as an interrupt pin, will triggered whenever the pin is changed 
	P1IES |=BIT1;				// setting as falling edge
    P1IFG &=~(BIT1);			// clearing interrupt flag

    _BIS_SR(LPM4_bits + GIE);	//enter LPM4 mode and enable global interrupt
}
 
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)	// will execute code once interrupt is triggered
{   
	P3OUT ^= BIT4; 				// changing states of P1.1
    do (i--);
    while (i != 0);
    P1IFG &=~(BIT1); 			// clears interrupt flag
}
