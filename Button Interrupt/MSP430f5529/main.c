#include <msp430.h> 

// Button Interrupt for 5529, leds switch one on and off with 200000 delay and with button pressed. 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;              // setting bit 0 of port 1 output to 1
	P4DIR |= BIT7;              // setting bit 6 of port 1 output to 1
    P1REN = BIT1;				// enable port 1 resister
	P1IE = BIT1;    			// setting bit 3 of port 1 as an interrupt pin, will triggered whenever the pin is changed 
    __enable_interrupt(); 		// initialize and enable the interrupt in the code
    while(1){  }
}
 
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)	// will execute code once interrupt is triggered
{   
	__delay_cycles(200000);		// set delay to 200000
	P1OUT ^= BIT0;
	P1IFG = ~BIT1;

	__delay_cycles(200000);
	P4OUT ^= BIT7;
	P1IFG = ~BIT1;
}
