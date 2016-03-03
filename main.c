#include <msp430f4152.h>
#include "main.h"
#include "rtc.h"
#include "LCD.h"
#include "temperature.h"
#include "UI.h"

volatile unsigned char frameCount = 1;     // the frame number for the animation
volatile unsigned char timeDirection = 0;  // the direction in which the frameCount is incremented.

volatile unsigned int blinkCounter = 0;
volatile unsigned char blinkFlag = 0;

unsigned char gRTCHundreths = 0;  // TODO clean?
unsigned char gOldRTCSecond = 0;  // TODO clean? used to track when the second flips for the use by the hundreths counter
 
//unsigned char gLowBattFlag = 0;   // sets to 1 if battery is low
 
volatile unsigned char btn_TLState, btn_BLState, btn_BRState;


void main(void) {
	// char i = 0;
	// int h, m, s;
	// int j = 0;


	WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
	FLL_CTL0 |= XCAP11PF;                     // Configure load capacitance of watch crystal (12.5 pf)

	// set to 8Mhz otherwise defaults to 1Mhz
	/*SCFI0 |= FN_4;                            // x2 DCO freq, 8MHz nominal DCO
 	 SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 Mhz
 	 FLL_CTL0 |= DCOPLUS + XCAP11PF;           // DCO+ set so freq= xtal x D x N+1
	 */

	// Note RTC module shares Basic Timer control register
	// BT is controlled by RTCHOLD
	RTCCTL = /*RTCBCD+*/                            // RTC enable, BCD mode,
           RTCHOLD+
           RTCMODE_3+                               // calendar mode
           /*RTCTEV_2+*/                            // Interupt every night at midnight
           RTCTEV_0 +                               // Interupt every minute
           RTCIE;                                   // interupt enabled - disable to allow basic timer interupts
                                                     
                                        

	// rtc seems to predivide the clock source by 128
	// making 256 pulses per second
	// therefor further dividing by 256 = 1 per sec
	// 256 / 4 = 64 time per sec
	// 256 / 2 = 128 times per second
	//IE2 |= BTIE;                               // enable basic timer interrupts
	//BTCTL += BT_fCLK2_DIV4;                    // 4ms interrupts

	// Setup LCD
	P2SEL = 0xFF;                              // port 2 select LCD mode
	P3SEL = 0xFF;                              // port 3 select LCD mode
	P4SEL = 0xFF;                              // port 4 select LCD mode
	P5SEL = 0xF7;                              // port 5 select LCD & 5.3 as I/O for led
  
	// use lcd_a module becuase it has software voltage/contrast control
	LCDACTL = LCDON + LCD3MUX + LCDFREQ_192;    // lcd on, lcd 3 mux, lcd freq to 192
	LCDAPCTL0 = LCDS0 + LCDS4 + LCDS8 + LCDS12 + LCDS16 + LCDS20; // select segments 1 - 23
	LCDAVCTL0 = LCDCPEN;                       	// enable internal LCD charge pump
	LCDAVCTL1 = VLCD_12;                       	// set charge pump to 3.26V
	//LCDAVCTL1 = VLCD_15;                       // set charge pump to 3.32V
	//LCDAVCTL1 = VLCD_2;                        // set charge pump to 2.66V


	// Set up Timer_A
	// basic timer is used by RTC so use Timer A for general app/main interrupts
	// used for polling button input
	CCTL0 = CCIE;                             	// CCR0 interrupt enabled
	TACCR0 = TENFPS;                         	// interrupt every .33 seconds
    
	TACTL = TASSEL_1 + MC_1;                  	// ACLK, up mode


	// Set up Timer_A_1
	// Timer_A_1 will be used for Frame rate timing by clearing the LPM3 flag to enable main loop
	TA1CCTL0 = CCIE;                              // TA1 CCRO interrupts enabled
	TA1CCR0 = 5461;                               // set to 6 fps
	TA1CTL = TASSEL_1 + MC_1;                     // ACLK, UP mode

	// setup button i/o's for 1.6, 1.7, 6.3
	P1SEL = 0x00;  									// set p1 to i/o
	P1OUT = 0;                               		// set all p6 outputs to low to save power
	P1DIR = ~(BIT6 | BIT7);                      	// set p1.6 and p1.7 to input / the rest to output
	P1IFG = 0x00;                                	// Clear all P1 interrupt flags
	//P1IE |= BIT6 + BIT7;                         	// enable interupts for p1.6 & p1.7
         
	// set up  button p6.3 (P6 does not have interrupt capabilities)
   P6SEL = 0;                             			// set p6.3 to i/o
   P6DIR = ~BIT3;                             		// set p6 to input
   P6OUT = 0;                                 		// set all p6 outputs to low to save power

   // set LED p5.3 to output mode
   P5DIR = BIT3;
   P5OUT = BIT3; // turn on led for testing
   // clear P5
   P5OUT = 0;
  
   // init port 7 as low output to save power
   // should only be set in Release version as it prevents the debugger from working properly.
	#ifdef DEBUG
  	  // do nothing
    #else
  	  // init port 7
	  P7OUT = 0;
	  P7SEL = 0x00; // i/o
	  P7DIR = 0xFF; // all inputs - set 7.4 to out
	#endif

	// init low voltage detector SVS
	// SVS uses considerable power so disabled here.
	//SVSCTL = VLD2;           //VLD0 - 1.9 V low voltage threshhold
                               //VLD1 - 2.1 V
                               //VLD2 - 2.3
                               //VLD3 - 2.8

 
  initRTC();

  clearLCD();

  //  Main Loop - UI Dispatch main enter LPM3 at end of loop
  // interrupt handler timerA1 clears LPM3 to restart loop.
  UI_dispatchMain();
  __bis_SR_register(LPM3_bits + GIE);                 // Enter LPM3 w/ interrupt
}



//----------------------------------------------------------------------------
// PORT1 interrupt handler for p1.6 & p1.7
// This could be used in place of the Timer A interupt below to detect button presses on p1.6 and p1.7
// however the button on p6.3 does not suppurt interupts
// TODO look for button up see example at:
// http://e2e.ti.com/support/microcontrollers/msp43016-bit_ultra-low_power_mcus/f/166/t/154444.aspx
//-----------------------------------------------------------------------------
/*
#pragma vector=PORT1_VECTOR
__interrupt void PORT1ISR(void)
{

  unsigned char iFlags = P1IFG & P1IE;


  P1IFG = 0x00; // Clear all P1.x  interrupt flags


// make sure we wait to handle signal noise
// can't change modes while in mode display 
  
  if(displayModeFlag == 0){
    // enter mode display function
    displayModeFlag = 1;
    if(iFlags & BIT7) btn_TLFlag = 1;
    if(iFlags & BIT6) btn_BLFlag = 1;
   
    //UI_dispatchEvent(btn_TLFlag, btn_BLFlag, btn_BRFlag);

   
    // turn on led
    //P5OUT = BIT3; 

  } // if displayModeFlag
  
}
*/
// Timer A0 interrupt service routine -
// handles IO - Note: debounce code is not necessary since we only pole a few times a second...

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

	unsigned char btn_TLChangeFlag = 0 ;
	unsigned char btn_BLChangeFlag = 0 ;
	unsigned char btn_BRChangeFlag = 0 ;
	unsigned char old_btn_TLState = btn_TLState;
	unsigned char old_btn_BLState = btn_BLState;
	unsigned char old_btn_BRState = btn_BRState;

	// get state of buttons
	btn_TLState = ((P1IN & BIT7) > 0) ? 1 : 0;
	btn_BLState = ((P1IN & BIT6) > 0) ? 1 : 0;
	btn_BRState = ((P6IN & BIT3) > 0) ? 1 : 0;

	// see if button state has changed
	btn_TLChangeFlag = btn_TLState ^ old_btn_TLState;
	btn_BLChangeFlag = btn_BLState ^ old_btn_BLState;
	btn_BRChangeFlag = btn_BRState ^ old_btn_BRState;

	// if changed dispatch event
	if(btn_TLChangeFlag | btn_BLChangeFlag | btn_BRChangeFlag){
		// state of buttons changed so dispatch event
		 UI_dispatchEvent(btn_TLState, btn_BLState, btn_BRState);
	}


   //_BIC_SR_IRQ(LPM3_bits);                 // Clear LPM3 bits from 0(SR)
}


// Timer A1 interrupt service routine
// setup to be services according to the framerate of the animation
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1 (void)
{     
    //unsigned int temp = TAIV;  

    frameCount = (frameCount < 6) ? frameCount+1 : 1;

    blinkFlag ^= 1;
    _BIC_SR_IRQ(LPM3_bits);                 // Clear LPM3 bits from 0(SR)

}

// Basic Timer interrupt service routine
// used by the RTC if rtc interrupts enabled
// shared between RTC and basic timer

#pragma vector=BASICTIMER_VECTOR
__interrupt void basic_timer(void)
{


}


