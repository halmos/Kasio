
#include <stdlib.h>
#include <msp430f4152.h>
#include "timeStampDefs.h"
#include "rtc.h"
#include "lcd.h"
#include "UI.h"

//unsigned int hundredthsCounter = 1;
//unsigned char RTC_SW_Hundredths = 0;
//unsigned char RTC_SW_Secs = 0;
//unsigned char RTC_SW_Mins = 0;
unsigned int build_year_YY = 0;
unsigned char build_int_month = 0;
unsigned char build_int_day = 0;
unsigned char build_int_hour = 0;
unsigned char build_int_minute = 0;
unsigned char build_int_second = 0;
unsigned long int gSecsToday = 0;

void initRTC(void){
 // Init time


/*
  build_int_month = BUILD_MONTH;   // prcompiler places o before month so there is a problem that the compiler thinks it is an octal number
  build_int_day = BUILD_DAY;
  build_int_hour = BUILD_HOUR;
  build_int_minute = BUILD_MINUTE;
  build_int_second = BUILD_SECOND;

  build_year_YY = BUILD_INT_YEAR - 2000;  // returns year in BCD format
*/

  // Init date
  //RTCDOW =  0x02;                       // Set DOW
  
   //day = BUILD_BCD_DAY;
 
  
  RTCSEC =  bcd2int(BUILD_BCD_SECOND);                       // Set Seconds
  RTCMIN =  bcd2int(BUILD_BCD_MINUTE);                       // Set Minutes
  RTCHOUR = bcd2int(BUILD_BCD_HOUR);                       // Set Hours

  //RTCDAY =  bcd2int(BUILD_BCD_DAY);                         // Set Day (DAY OF MONTH 1-31)
 // RTCMON =  bcd2int(BUILD_BCD_MONTH);                       // Set Month
 // RTCYEAR = BUILD_INT_YEAR;                     // RTC years is stored in two seperate bytes
  //year = BUILD_YEAR >> (8 + BUILD_YEAR & 0xFF)
  //RTCDOW = 3;//dow(BUILD_INT_YEAR,RTCMON,RTCDAY);

  RTCCTL &= ~RTCHOLD;                   // Enable RTC

}

void RTC_incMin(void){
     unsigned int intMin = RTCMIN;
     intMin++;
     if (intMin > 59){
        intMin = 0;
     }
     RTCMIN = intMin;

}
void RTC_decMin(void){
     unsigned int intMin = RTCMIN;
    
     if (intMin > 0){
        intMin--;
     } else {
       intMin = 59;
     }

     RTCMIN = intMin;

}

void RTC_incHour(void){
     unsigned int intHour = RTCHOUR;
     intHour++;
     if (intHour > 23){
        intHour = 0;
     }
     RTCHOUR = intHour;


}
void RTC_decHour(void){
     unsigned int intHour = RTCHOUR;
    
     if (intHour > 0){
        intHour--;
     } else {
       intHour = 23;
     }

     RTCHOUR = intHour;

}

void RTC_incSec(void){
     unsigned int intSec = RTCSEC;
     intSec++;
     if (intSec > 59){
        intSec = 0;
     }
     RTCSEC = intSec;


}
void RTC_decSec(void){
     unsigned int intSec = RTCSEC;
    
     if (intSec > 0){
        intSec--;
     } else {
       intSec = 59;
     }

     RTCSEC = intSec;

}

void RTC_resetSec(void){
     RTCSEC = 0;
}

void RTC_incMonth(void){
     unsigned int intMonth= RTCMON;
     intMonth++;
     if(intMonth > 12){
                 intMonth = 1;
     }
     RTCMON = intMonth;
}
void RTC_decMonth(void){
     unsigned int intMonth= RTCMON;
     intMonth--;
     if(intMonth < 1){
                 intMonth = 12;
     }
     RTCMON = intMonth;
}
void RTC_incDOW(void){
     unsigned int intDOW = RTCDOW;
     intDOW++;
     if(intDOW>7)intDOW = 1;
     RTCDOW = intDOW;

}

void RTC_incDate(void){
      unsigned int intDate= RTCDAY;
     intDate++;
     if(intDate > 31){
                 intDate = 1;
     }
     RTCDAY = intDate;
}

void RTC_decDate(void){
     unsigned int intDate= RTCDAY;
     intDate--;
     if(intDate < 1){
                 intDate = 31;
     }
     RTCDAY = intDate;
}

void RTC_incYear(void){
      unsigned int intYear= RTCYEAR;
     intYear++;
     if(intYear > 3000){
                 intYear = 3000;
     }
     RTCYEAR = intYear;
}
void RTC_decYear(void){
      unsigned int intYear= RTCYEAR;
     intYear--;
     if(intYear < 2010){
                 intYear = 2010;
     }
     RTCYEAR = intYear;
}
int int2bcd(int dec)
{
  return ((dec/10)<<4)+(dec%10);
}

int bcd2int(int bcd)
{
return ((bcd>>4)*10)+bcd%16;
}


void testRTC(void){
    
     for(;;){
        //debug_printf("S: %d \n", RTCSEC);
       // setHours(RTCHOUR);
       // setMins(RTCMIN);
       // setSecs(RTCSEC);
        setBCDHours(RTCHOUR);
        setBCDMins(RTCMIN);
        setBCDSecs(RTCSEC);
        // Enter LPM3 w/ interrupts   
        _BIS_SR(LPM3_bits + GIE);
     
         }
}
/*
void testStopwatch(void){
     for(;;){
      setBCDMins(RTCSEC);
      setSecs(RTC_SW_Hundredths);
      _BIS_SR(LPM3_bits + GIE);
     }
}
*/
/*
void RTC_incStopwatch(void){
     
  extern unsigned char currentMode;  // the current mode from the UI
  extern unsigned char currentSubMode;

  if((currentMode == MODE_STOPWATCH) && (currentSubMode == MODE_STOPWATCH_RUN)){
     // running off of TimerA1 interrupts 32 times per second
     RTC_SW_Hundredths = (hundredthsCounter * 100) / 32;
    
      hundredthsCounter++;
      if(hundredthsCounter == 32){
         // 1 tenth of second increment
         hundredthsCounter = 1;
          //P5OUT ^= BIT3;
         //toggle led
  
         RTC_SW_Secs++;
         if(RTC_SW_Secs > 59){
            RTC_SW_Secs = 0;
            RTC_SW_Mins++;
            if(RTC_SW_Mins>60){
              RTC_SW_Mins = 0;
            }
         } // if secs > 59  
      } // if hundedths > 32
  } // if currentMode
}

void RTC_resetStopWatch(void){
     RTC_SW_Secs = 0;
     RTC_SW_Mins = 0;
     RTC_SW_Hundredths = 0;
     hundredthsCounter = 0;
}
*/
// function to find day of the week
// http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#cite_ref-3
 int dow(int y, int m, int d)
   {
       static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
       y -= m < 3;
       return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
   }
