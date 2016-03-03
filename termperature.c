/*
 * Conversion formulas from http://www.43oh.com/forum/viewtopic.php?t=2474
 *
 * ADC to degrees Celsius:
 * C = (A * 27069L - 18169625L) >> 16
 *
 * ADC to degrees Kelvin:
 * K = (A * 27069L - 268467L) >> 16
 *
 * ADC to degrees Farenheit:
 * F = (A * 48724L - 30634388L) >> 16
 *
 * The 'L' character after the integer forces it to be a 32-bit signed long.
 */

#include <msp430f4152.h>
#include "temperature.h"
#include "LCD.h"


// it's okay to run this at any MCU clockrate since it uses its own ADC10OSC clock
void chiptemp_setup()
{
    //ADC10CTL0 = SREF_1 + ADC10SHT_3 + ADC10SR + REFON + ADC10ON;
    //ADC10CTL1 = INCH_10 + ADC10DIV_3;   // Channel 10 = Temp Sensor
}
 
int chiptemp_read()
{
    unsigned adc;

    ADC10CTL0 = SREF_1 + ADC10SHT_3 + ADC10SR + REFON + ADC10ON;
    ADC10CTL1 = INCH_10 + ADC10DIV_3;   // Channel 10 = Temp Sensor


    // ENC = enable conversion, ADC10SC = start conversion
    ADC10CTL0 |= ENC + ADC10SC;
    while (!(ADC10CTL0 & ADC10IFG))
        /* wait until conversion is completed */ ;
 
    adc = ADC10MEM;
 
    // shut off conversion and lower flag to save power.
    // ADC10SC is reset automatically.
    while (ADC10CTL0 & ADC10BUSY)
        /* wait for non-busy per section 22.2.6.6 in User's Guide */ ;
    ADC10CTL0 &= ~ENC;
       
    // DIABALE ADC TO SAVE POWER
    ADC10CTL0 = 0;
  
    // return degrees F
    return (int)((adc * 48724L - 30634388L) >> 16);
}

/*
void chiptemp_readstr(char *str, unsigned len)
{
    snprintf(str, len, "%d%c F", chiptemp_read(), 176);
}
*/
void testTemp()
{
    int t;             // 'volatile' required to prevent the optimizer from optimizing it out
 /*
    WDTCTL = WDTPW + WDTHOLD;
    __enable_interrupt();           // not used -- but for realism
 */

    t = 0;
   
    while (1) {
        __delay_cycles(0xFFFF);     // <-- set break/watchpoint here
        t = chiptemp_read();
        setSecs((char)t);
        __delay_cycles(0xFFFF);     // <-- set break/watchpoint here
    }
}
