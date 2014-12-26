################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/msp430_4.3.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./usr/ADS1118.obj" \
"./usr/LCD_driver.obj" \
"./usr/UART_TxRx.obj" \
"../lnk_msp430g2553.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include usr/subdir_vars.mk
-include subdir_rules.mk
-include usr/subdir_rules.mk
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
ADS1118_LaunchPad.out \

EXE_OUTPUTS__QUOTED += \
"ADS1118_LaunchPad.out" \


# All Target
all: ADS1118_LaunchPad.out

# Tool invocations
ADS1118_LaunchPad.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi -g --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal -z --stack_size=80 -m"ADS1118_LaunchPad.map" --heap_size=80 -i"c:/ti/ccsv6/ccs_base/msp430/include" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/lib" -i"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --reread_libs --warn_sections --display_error_number --xml_link_info="ADS1118_LaunchPad_linkInfo.xml" --rom_model -o "ADS1118_LaunchPad.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(GEN_OPTS__QUOTED)$(GEN_CMDS__QUOTED)
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "main.pp" "usr\ADS1118.pp" "usr\LCD_driver.pp" "usr\UART_TxRx.pp" 
	-$(RM) "main.obj" "usr\ADS1118.obj" "usr\LCD_driver.obj" "usr\UART_TxRx.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/hex430" --ti_txt "ADS1118_LaunchPad.out" -o "ADS1118_LaunchPad.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

