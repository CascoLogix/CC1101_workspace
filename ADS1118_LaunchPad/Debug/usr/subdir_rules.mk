################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
usr/ADS1118.obj: ../usr/ADS1118.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/ADS1118_LaunchPad/usr" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/ADS1118.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usr/LCD_driver.obj: ../usr/LCD_driver.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/ADS1118_LaunchPad/usr" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/LCD_driver.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

usr/UART_TxRx.obj: ../usr/UART_TxRx.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/ADS1118_LaunchPad/usr" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="usr/UART_TxRx.pp" --obj_directory="usr" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


