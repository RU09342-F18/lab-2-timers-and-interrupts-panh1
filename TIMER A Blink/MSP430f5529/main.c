#include <msp430.h>

// Timer A Blink for 5529, 

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= BIT0;              // setting bit 0 of port 1 output to 1
    TB0CCTL0 = CCIE;            // enabling interrupt
	TBCTL = TBSSEL_2 + MC_2;    // setting to continuous mode


    __enable_interrupt(); 		// initialize and enable the interrupt in the code
}
 
#pragma vector=TIMER0_B0_VECTOR // Interrupt
__interrupt void Timer_B(void)	// will execute code once interrupt is triggered
{   
	P1OUT ^= BIT0;              // Toggle LED
}
