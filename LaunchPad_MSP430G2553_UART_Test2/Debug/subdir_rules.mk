################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
GPIO.obj: ../GPIO.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/LaunchPad_MSP430G2553_UART_Test2" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="GPIO.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

USCI.obj: ../USCI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/LaunchPad_MSP430G2553_UART_Test2" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="USCI.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/LaunchPad_MSP430G2553_UART_Test2" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


