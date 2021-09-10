#include <msp430.h> 

volatile unsigned int i = 0;

/**
 * main.c
 */
int main(void)
{
  // Stop watchdog timer. This line of code is needed at the beginning of most MSP430 projects.
  // This line of code turns off the watchdog timer, which can reset the device after a certain period of time.
	WDTCTL = WDTPW + WDTHOLD;

	/*  P4DIR is a register that configures the direction or a port pin as an output or an input
	 *  To set a specific pin as input or output, we write 1 or 0 on the appropriate bit of the register
	 *  P4DIR = PIN7, PIN6, PIN5, PIN4, PIN3, PIN2, PIN1, PIN0
	 *  Since we want to blink LED2 on the experimenter board, we want to set the direction of port 4, Pin0 (P4.0) as an output.
	 *  The pinout for this is shown on the experimenter board next to the LED.
	 *
	 *  To set the P4.0 as output, we therefore need to write out:
	 *
	 *  P4DIR = 0000 0001
	 *
	 *  Which sets all pins on port 4 except 4.0 to input. In shorthand we can just assign 0x01 HEX.
	 *
	 *  P4DIR |= 0x01 is equivalent to P4DIR = P4DIR | 0x01
	 */
	P4DIR |= 0x01;
	P1DIR |= 0x01;
	P5DIR |= 00100000;

	/*
	 * Disable GPIo power-on default high-impedance mode to activate previously configured port settings
	 */
	PM5CTL0 &= ~LOCKLPM5;

	P1OUT = 00000000;
	while(1)
	{
	    /*
	     * Toggle port 4, pin 0 using XOR (^)
	     * P4OUT is another register which holds the status of the LED, 1 = on, 0 = off
	     * P4OUT ^= 0x01 is equivalent to P4OUT = P4OUT ^ 0x01
	     * Effectively, P4OUT = 1 ^ 1 -> 0 or P4OUT = 0 ^ 1 -> 1
	     * This is because ^ is a XOR operation meaning it changes only when the bits are different
	     * This, in turn, has the effect of toggling the LED every cycle
	     */
	    P4OUT ^= 00000001;
	    P1OUT ^= 00000001;
	    P5OUT ^= 00100000;
	    __delay_cycles(1000000);
	}

	return 0;
}
