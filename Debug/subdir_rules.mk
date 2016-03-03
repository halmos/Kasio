################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LCD.obj: ../LCD.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi --preinclude="C:/Users/Erik/Documents/watch of confusion/Kasio/debugFlag.h" --include_path="C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" --include_path="C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power="all" -g --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="LCD.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UI.obj: ../UI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi --preinclude="C:/Users/Erik/Documents/watch of confusion/Kasio/debugFlag.h" --include_path="C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" --include_path="C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power="all" -g --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="UI.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi --preinclude="C:/Users/Erik/Documents/watch of confusion/Kasio/debugFlag.h" --include_path="C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" --include_path="C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power="all" -g --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rtc.obj: ../rtc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi --preinclude="C:/Users/Erik/Documents/watch of confusion/Kasio/debugFlag.h" --include_path="C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" --include_path="C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power="all" -g --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="rtc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

termperature.obj: ../termperature.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi --preinclude="C:/Users/Erik/Documents/watch of confusion/Kasio/debugFlag.h" --include_path="C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" --include_path="C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --advice:power="all" -g --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="termperature.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


