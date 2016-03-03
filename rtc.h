#ifndef FILE_RTC_SEEN
#define FILE_RTC_SEEN


void initRTC(void);
void testRTC(void);
void testStopwatch(void);
int dow(int, int, int);
void RTC_incSec(void);
void RTC_decSec(void);
void RTC_resetSec(void);

void RTC_incMin(void);
void RTC_decMin(void);
void RTC_incHour(void);
void RTC_decHour(void);
void RTC_incMonth(void);
void RTC_decMonth(void);
void RTC_incDOW(void);
void RTC_incDate(void);
void RTC_decDate(void);
void RTC_incYear(void);
void RTC_decYear(void);

int int2bcd(int);
int bcd2int(int);


#endif /*FILE_RTC_SEEN */
