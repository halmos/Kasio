#ifndef FILE_LCD_SEEN
#define FILE_LCD_SEEN

#define segA 0x01
#define segB 0x02
#define segC 0x04
#define segD 0x08
#define segE 0x10
#define segF 0x20
#define segG 0x40
#define segH 0x80 // used for the extra vertical segment of the 1st DOW digit

#define seg0 0x01
#define seg1 0x02
#define seg2 0x04
#define seg3 0x08
#define seg4 0x10
#define seg5 0x20
#define seg6 0x40
#define seg7 0x80

/*
 a1a
f   b
6   2
 g7g
e   c
5   3
 d4d
*/

#define _a 0
#define _b 1
#define _c 2
#define _d 3
#define _e 4
#define _f 5
#define _g 6
#define _h 7

#define _A_ 10
#define _B_ 11
#define _C_ 12
#define _D_ 13
#define _E_ 14
#define _F_ 15
#define _G_ 16
#define _H_ 17
#define _I_ 18
#define _J_ 19
#define _K_ 20
#define _L_ 21
#define _M_ 22
#define _N_ 23
#define _O_ 24
#define _P_ 25
#define _Q_ 26
#define _R_ 27
#define _S_ 28
#define _T_ 29
#define _U_ 30
#define _V_ 31
#define _W_ 32
#define _X_ 33
#define _Y_ 34
#define _Z_ 35
#define _NEG_ 36
#define _UP_  37
#define _DWN_ 38
#define _SP_ 39
#define _SML7_ 40
#define _SLSH_ 41
#define _SMLo_  42

#define _SMLr_ 43



#define sound 0x10
#define alarm 0x01
#define H24 0x04
#define colon 0x02
#define lap 0x01
#define PM 0x40





void testLCD(void);
void clearLCD(void);

void setBCDHours(char);
void setHours(char);
void setHourSegs(char, char);
void clearHours(void);

void setBCDMins(char);
void setMins(char);
void setMinsSegs(char, char);
void clearMins(void);

void setSecs(char);
void setBCDSecs(char);
void setSecsSegs(char, char);
void clearSecs(void);


void showTime(char, char, char);
void showNumber(unsigned long );


void setDay(char);
void setDaySegs(char digitA, char digitB, unsigned int segMask);
void clearDay(void);

void setDate(char);
void setDateSegs(char,char);
void setBCDDate(char);
void clearDate(void);

void setMonth(char);

void setSecsColon(char);
void setH24Icon(char state);
void setLED(char state);
void setSoundIcon(char state);

void testLCD_bitByBit(void);
void testLCD_contrast(void); 

#endif /* FILE_LCD_SEEN */
