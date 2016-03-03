set TIMESTAMP=%TIME: =0%
echo #define BUILD_TIME %TIMESTAMP% > ..\timeStampDefs.h
echo #define BUILD_HOUR %TIMESTAMP:~0,2% >> ..\timeStampDefs.h
echo #define BUILD_MINUTE %TIME:~3,2% >> ..\timeStampDefs.h
echo #define BUILD_SECOND %TIME:~6,2% >> ..\timeStampDefs.h
echo #define BUILD_DAY %DATE:~7,2%  >> ..\timeStampDefs.h
echo #define BUILD_MONTH %DATE:~4,2% >> ..\timeStampDefs.h
echo #define BUILD_INT_YEAR %DATE:~-4%  >> ..\timeStampDefs.h
echo #define BUILD_BCD_HOUR 0x%TIMESTAMP:~0,2%  >> ..\timeStampDefs.h
echo #define BUILD_BCD_MINUTE 0x%TIME:~3,2%  >> ..\timeStampDefs.h
echo #define BUILD_BCD_SECOND 0x%TIME:~6,2% >> ..\timeStampDefs.h
echo #define BUILD_BCD_DAY 0x%DATE:~7,2%  >> ..\timeStampDefs.h
echo #define BUILD_BCD_MONTH 0x%DATE:~4,2% >> ..\timeStampDefs.h