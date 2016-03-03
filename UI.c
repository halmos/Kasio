//#include <msp430f4152.h>
#include "msp430.h"
#include "UI.h"
#include "LCD.h"
#include "RTC.h"


unsigned char currentMode = MODE_SHOW_TAPATTERN;
unsigned char currentSubMode = 0;
unsigned char infoAnimMask = 0x80;


/* ***************************************
 function to handle which function to run
 ***************************************** */
void UI_dispatchMain(void){
     extern unsigned char blinkFlag;

    while(1){
                        
        //LEDOFF
        switch(currentMode){
            case MODE_SHOW_TIME24:
            	UI_show24HourTime();
                // manage LED
                P5OUT = (P1IN & BIT7) ? BIT3 : 0;
            	break;
            case MODE_INFO:
            	 // manage LED
            	 P5OUT =  0;
            	 UI_showInfo();
                 break;
            case MODE_SLEEP:
                 break;
            case MODE_SET_TIME_HOUR:
            	// manage LED
            	P5OUT =  0;
                UI_showSetTime(blinkFlag,1,1,1,1);
                break;
            case MODE_SET_TIME_MIN:
                UI_showSetTime(1,blinkFlag,1,1,1);
                break;
            case MODE_SET_TIME_SEC:
                UI_showSetTime(1,1,blinkFlag,1,1);
                break;
            default: 
                // in case something happened and a mode is set that has not been caught
                currentMode = MODE_SHOW_TIME24;
                break;
        }
        //sleep
        //P5OUT = 0;
        // use this to find the duty cycle of the CPU and est. power usage
        //showNumber(TA1R);
        _BIS_SR(LPM3_bits + GIE);
    }//while loop
}

/* ***************************************
 function to handle button events
 ***************************************** */

void UI_dispatchEvent(unsigned char TL, unsigned char BL, unsigned char BR){
    // light should be on whenever TL is pressed down

    // if(TL == 1) setLightOn();
    
    if((TL| BL | BR) == 0){
    	// no buttons down (all buttons released)
    	switch(currentMode){
    		case MODE_SHOW_TIME12:
    		case MODE_SHOW_TIME24:
    		case MODE_INFO:
    		case MODE_SLEEP:
    		case MODE_SET_TIME_HOUR:
    		case MODE_SET_TIME_MIN:
    		case MODE_SET_TIME_SEC:
    		case MODE_SET_DATE_DATE:
    		case MODE_SET_DATE_MONTH:
    		case MODE_SET_DATE_YEAR:
    		default:
    			 currentMode = MODE_SHOW_TIME24;
    	}

    } else if(TL & BL){
        // both left buttons are down - show info
    	switch(currentMode){
    	    case MODE_SHOW_TIME24:
    	      currentMode = MODE_INFO;
            case MODE_INFO:
              currentMode = MODE_SLEEP;
              UI_InitShowSleep();
              break;
    	}
    } else if((BL == 1) && (TL == 0) && (BR == 1)){  
        // BL & BR are pressed
        switch( currentMode){
        	case MODE_SET_SPEED:
        	case MODE_INFO:
        	case MODE_SHOW_TIME24:
            default:
            	 currentMode = MODE_SHOW_TIME24;
            	 break;
        }
    } else if((BL == 0) && (TL == 1) && (BR == 0)){
        // TL is pressed - increment time unit if in a time set mode
           switch(currentMode){
             case MODE_SET_TIME_HOUR:
                  RTC_incHour();
                  break;
              case MODE_SET_TIME_MIN:
                  // increment hour
                  RTC_incMin();
                  break;
              case MODE_SET_TIME_SEC:
                  // increment hour
                  //RTC_incSec();
                  RTC_resetSec();
                  break;
              case MODE_SLEEP:
              case MODE_INFO:
            	  break;
              default:
                currentMode = MODE_SHOW_TIME24;
                break;
         }
       
    } else if((BL == 1) && (TL == 0) && (BR == 0)){
        // only BL is pressed - change mode or if in time set mode decrement time unit
       // clearLCD();
        
        switch( currentMode){
        	case MODE_SLEEP:
        		break;
            case MODE_SET_TIME_HOUR:
                RTC_decHour();
                break;
            case MODE_SET_TIME_MIN:
                RTC_decMin();
                break;
            case MODE_SET_TIME_SEC:
                //RTC_decSec();
                 RTC_resetSec();
                break;
            case MODE_SET_DATE_DATE:
                RTC_decDate();
                break;
            case MODE_SET_DATE_MONTH: 
                RTC_decMonth();
                break;
            case MODE_SET_DATE_YEAR:      
                RTC_decYear();
                break;
        	}
    }  else if((BL == 0) && (TL == 0) && (BR == 1)){
        // BR is pressed -
        switch(currentMode){
            case MODE_SHOW_TAPATTERN:
            	currentMode = MODE_SHOW_TIME24;
            	break;
            case MODE_SHOW_TIME24:
                 currentMode = MODE_SHOW_TIME24;
                 break;
            case MODE_SET_TIME_HOUR:
                currentMode = MODE_SET_TIME_MIN;
                break;
            case MODE_SET_TIME_MIN:
                currentMode = MODE_SET_TIME_SEC;
                break;
            case MODE_SET_TIME_SEC:
                 currentMode = MODE_SET_DATE_DATE;
            	 break;
            case MODE_SET_DATE_DATE:
               currentMode = MODE_SET_DATE_MONTH;
                break;
            case MODE_SET_DATE_MONTH:
                currentMode = MODE_SET_DATE_YEAR;
                break;
            case MODE_SET_DATE_YEAR:
                 currentMode = MODE_SHOW_TIME24;
                 break;
            default:
                currentMode = MODE_SHOW_TIME24;
                break;
        }
    } else if((BL == 0) && (TL == 1) && (BR == 1)){
        // TL & BR is pressed -
        switch(currentMode){
    		case MODE_SHOW_TIME24:
            case MODE_SET_TIME_HOUR:
		    case MODE_SET_TIME_MIN:
		    case MODE_SET_TIME_SEC:
		    case MODE_SET_DATE_DATE:
		    case MODE_SET_DATE_MONTH:
		    case MODE_SET_DATE_YEAR:
		    	// exit time set mode
		    	currentMode = MODE_SHOW_TIME24;
		    	break;
        }
    }
}

void UI_showSetTime(char blinkHours, char blinkMins, char blinkSecs, char blinkDate, char blinkMonth){

     setH24Icon(1);
     setSecsColon(1);

     if(blinkHours){
          setHours(RTCHOUR);
        } else {
          clearHours();
        }

      if(blinkMins){
          setMins(RTCMIN);
        } else {
          clearMins();
        }

      if(blinkSecs){
          setSecs(RTCSEC);
        } else {
          clearSecs();
        }


      if(blinkDate){
          setDate(RTCDAY);
        } else {
          clearDate();
        }

      if(blinkMonth){
          setMonth(RTCMON);
        } else {
          clearDay();
        }

}

void UI_showSetYear(char blinkFlag){
     clearLCD();
       setDate(RTCDAY);
       setMonth(RTCMON);
     if(blinkFlag)showNumber(RTCYEAR);

}
void UI_InitShowSleep(void){
     clearLCD();
     setHourSegs(_S_,_L_);
     setMinsSegs(_E_,_E_);
     setSecsSegs(_P_,_SP_);

}



/*
void UI_showInfoStamp(void){
    //unsigned int temp;
    
    // show build date: MM:DD:YY
    setHours(BUILD_MONTH);
    setMins(BUILD_DAY);
    setSecs(BUILD_YEAR & 0xFF);
    
    setDate(BUILD_HOUR);
    
}
*/

void UI_show24HourTime(void){
	showTime(RTCHOUR, RTCMIN, RTCSEC);
}

void UI_showInfo(void){
	UI_showInfoHalmos();
}
void UI_showInfoHalmos(void){
    clearLCD();
    setHourSegs(_H_,_A_);
    setMinsSegs(_L_,_M_);
    setSecsSegs(0,5);
    
    
}

