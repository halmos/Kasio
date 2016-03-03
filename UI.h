#ifndef FILE_UI_SEEN
#define FILE_UI_SEEN

#define MODE_SET_TIME 10
#define MODE_SET_TIME_SEC 11
#define MODE_SET_TIME_HOUR 12
#define MODE_SET_TIME_MIN 13

#define MODE_SET_DATE 20
#define MODE_SET_DATE_MONTH 21
#define MODE_SET_DATE_DATE 22
#define MODE_SET_DATE_WD 23
#define MODE_SET_DATE_YEAR 24


#define MODE_INFO 60
#define MODE_INFO_SNAKE 61
#define MODE_INFO_STAMP 62
#define MODE_INFO_HALMOS 63
#define MODE_SHOW_TEMP 64

#define MODE_SLEEP 68

#define MODE_SHOW_TAPATTERN 70
#define MODE_SHOW_TIME12 71
#define MODE_SHOW_TIME24 72
#define MODE_SHOW_TIME24DELAY 73

#define MODE_SET_SPEED 75




void UI_dispatchEvent(unsigned char, unsigned char, unsigned char);
void UI_dispatchMain(void);

void UI_show24HourTime(void);
void UI_setTime_Inc(void);
void UI_showInfo(void);
void UI_showInfoHalmos(void);
void UI_showStopwatch(void);
void UI_InitShowSleep(void);

void UI_showSetYear(char blinkFlag);
void UI_showSetTime(char, char, char, char, char);


#endif /*FILE_UI_SEEN */
