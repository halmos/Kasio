#ifndef FILE_MAIN_SEEN
#define FILE_MAIN_SEEN

#define startH 12
#define modeDisplayLength 2   // counts in quarter seconds (4 = 1 sec) - sets the amount of a time user has to press button combo
                              // and determines pause between button press and mode switch

#define HUNDREDTHSINC 25 // the hundredths of a second elapsed per TIMERA call (CCRO)
#define TWOFPS 16384 
#define THREEFPS 10923
#define THREEHALFFPS 9362
#define FOURFPS 8192 //= c / 4 
#define FIVEFPS 6554 //= 32768 / 5 
#define EIGHTFPS 4096
#define TENFPS 3277
#define SIXTEENFPS 2048 // 32768 / 16

#define DEBOUNCELENGTH  0

#endif /* FILE_MAIN_SEEN */
