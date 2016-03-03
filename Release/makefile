################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./LCD.obj" \
"./auerbach_patterns.obj" \
"./dexterSinister.obj" \
"./main.obj" \
"./rtc.obj" \
"./ta_UI.obj" \
"./termperature.obj" \
"../lnk_msp430f4152.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
WatchCode-TA.out \

EXE_OUTPUTS__QUOTED += \
"WatchCode-TA.out" \

BIN_OUTPUTS += \
WatchCode-TA.hex \

BIN_OUTPUTS__QUOTED += \
"WatchCode-TA.hex" \


# All Target
all: WatchCode-TA.out secondary-outputs

# Tool invocations
WatchCode-TA.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O2 --opt_for_speed=5 --advice:power="all" --define=__MSP430F4152__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"WatchCode-TA.map" --heap_size=80 --stack_size=80 -i"C:/Msp430-ccs/ccsv6/ccs_base/msp430/include" -i"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/lib" -i"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="WatchCode-TA_linkInfo.xml" --rom_model -o "WatchCode-TA.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

WatchCode-TA.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/Msp430-ccs/ccsv6/tools/compiler/msp430_4.3.1/bin/hex430" --ti_txt -o "WatchCode-TA.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "LCD.pp" "auerbach_patterns.pp" "dexterSinister.pp" "main.pp" "rtc.pp" "ta_UI.pp" "termperature.pp" 
	-$(RM) "LCD.obj" "auerbach_patterns.obj" "dexterSinister.obj" "main.obj" "rtc.obj" "ta_UI.obj" "termperature.obj" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

