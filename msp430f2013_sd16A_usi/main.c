// Project name: MSP430AD_AD16
//
//  06March2014 .. initial verion .. KM
//
// See MSP430x2xx Family User's Guide -- slau144j.pdf for detailed information.
//
// VREF is nominally 1.2 volts.
// Normally want the gain = 1 for max input range.
// FSR is the full scale range and is VREF/2 (0.6V)
// Non-unipolar inputs goes +- FSR (+- 0.6V)
// Uni-polar inputs go from 0 to 0.6V
// Use a resistor divider at input if the source range exceed this.
//
// The analog inputs are differential.  Can use A4- as the reference
// to establish the "zero" point.
//
// The MSP430F2013 A/D does not have an input buffer.  It has been used
// successfully without an external one.  But this might be a consideration.
//
// Searching on the web, the effective number of bits for OSR=32 is about 10.
// The number of 16 (15?) is only for OSR=1024.  OSR=256 nominally gives 13-14.
//
// There is an overflow flag.  There must be a potential problem not discussed.
//
// If 10 A/D bits suffices for an application I recommend using the MSP4302012!
//
//  Pin  1 -- Vcc
//  Pin  2 -- P1.0  LED (high -> on)
//  Pin  3 -- P1.1  A4+ a/d input +
//  Pin  4 -- P1.2  A4- a/d input - (use to set input reference level)
//  Pin  5 -- P1.3  VREF out .. needs bypass capacitor
//  Pin  6 -- P1.4  P1.4 for timing sample rate
//  Pin  7 -- SCLK  (is P1.5)
//
//  Pin 14 -- GND
//  Pin 13 -- P2.6  free
//  Pin 12 -- FS   (is P2.7 used as SPI frame sync)
//  Pin 11 -- Spy-by-wire
//  Pin 10 -- Spy-by wire
//  Pin  9 -- SDI   (was p1.7)
//  Pin  8 -- SDO   (was p1.6)


#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;            // Stop watchdog timer

  // setup port 1 pin properties
  P1DIR = BIT0|BIT4|BIT5|BIT6;         // these pins are outputs
  P1SEL = BIT3;                       // to connect VREF to P1.3

  // set up SPI peripheral
  USICTL0 = USIPE7|USIPE6|USIPE5|USIMST|USIOE;
  USICKCTL = USIDIV_1|USISSEL_2;
  P2SEL = 0;           // initialize
  P2DIR = BIT7;        // set p2.7 as output for frame sync
  P2OUT &= ~BIT7;      // set frame sync low at start up

  // set up SD16_A delta-sigma converter
  SD16CTL = SD16REFON + SD16SSEL_1;   // 1.2V ref, SMCLK
  SD16INCTL0 = SD16INCH_4;            // A4 +/-  also sets gain to 1
  SD16CCTL0 = SD16IE;     // bipolar, offset binary, interrupt enable, 256 OSR, continuous
  SD16AE = SD16AE4;       // Select AD channel 4
  SD16CCTL0 |= SD16SC;    // Set bit to start first conversion

  _BIS_SR(GIE);           // keep powered, running and allow interrupts

  while(1);				  // nothing else to do
}

// Interrupt service routine.  Only runs when needed.

unsigned int value;

#pragma vector = SD16_VECTOR
__interrupt void SD16ISR(void)
{
  P1OUT &= ~BIT4;         // start of interrupt service, used to check sample rate
  P2OUT |= BIT7;          // end previous frame by frame sync going high

  value = SD16MEM0;       // read the sample and clear interrupt flag
  if (value < 0x7FFF)     // SD16MEM0 > middle of range
    P1OUT &= ~BIT0;
  else
    P1OUT |= BIT0;

  // send sample value as SPI
  USISRL = value;         // load SPI shift register with low 8 bits of sample
  USISRH = (value>>8);    // load high 8 bits of the sample
  P2OUT &= ~BIT7;         // generate frame sync high to low transition
  USICNT = 16 | USI16B;   // load counter starting the SPI transferr

  P1OUT |= BIT4;          // end of interrupt service
}







/////////////////////
/*
uint16_t RXdata;

int main(void)
{
  // ADC
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= 0x01;                            // Set P1.0 to output direction
  SD16CTL = SD16REFON + SD16SSEL_1;         // 1.2V ref, SMCLK
  SD16INCTL0 = SD16INCH_1;                  // A1+/-
  SD16CCTL0 =  SD16UNI + SD16IE;            // 256OSR, unipolar, interrupt enable
  SD16AE = SD16AE2;                         // P1.2 A1+, A1- = VSS
  SD16CCTL0 |= SD16SC;                      // Set bit to start conversion

  // SPI Slave
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1OUT =  0x10;                        // P1.4 set, else reset
  P1REN |= 0x10;                        // P1.4 pullup
  P1DIR = 0x01;                         // P1.0 output, else input
  USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave
  USICTL1 |= USIIE;                     // Counter interrupt, flag remains set
  USICTL0 &= ~USISWRST;                 // USI released for operation
  USISRL = P1IN;                        // init-load data
  USICNT = 16;                          // init-load counter

  _BIS_SR(LPM0_bits + GIE);					// Enter LPM0 w/ interrupt
}

#pragma vector = SD16_VECTOR
__interrupt void SD16ISR(void)
{
  if (SD16MEM0 < 0x7FFF)           	    // SD16MEM0 > 0.3V?, clears IFG
    P1OUT &= ~0x01;
  else
    P1OUT |= 0x01;
}

// USI interrupt service routine
#pragma vector = USI_VECTOR
__interrupt void universal_serial_interface(void)
{
  if (0x10 & USISRL)
    P1OUT |= 0x01;
  else
    P1OUT &= ~0x01;
  USISRL = P1IN;
  USICNT = 16;                           // re-load counter
}
*/

