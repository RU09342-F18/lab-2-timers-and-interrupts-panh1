#include <msp430.h> 

// Button Interrupt for G2

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;              // setting bit 0 of port 1 output to 1
	P1DIR |= BIT6;              // setting bit 6 of port 1 output to 1
    P1REN = BIT3;				// enable port 1 resister
	P1OUT = 0xff;				// setting all the port 1 registers output to 1
	P1IE = BIT3;    			// setting bit 3 of port 1 as an interrupt pin, will triggered whenever the pin is changed 
    __enable_interrupt(); 		// initialize and enable the interrupt in the code
    while(1){  }
}
 
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)	// will excute code once interrupt is triggered 
{   
	__delay_cycles(300000);		// set delay to 300000
	P1OUT ^= BIT0;
	P1IFG = ~BIT3;

	__delay_cycles(300000);
	P1OUT ^= BIT6;
	P1IFG = ~BIT3;
}
