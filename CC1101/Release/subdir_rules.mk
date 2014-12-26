################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CC1101.obj: ../CC1101.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=eabi -O2 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="CC1101.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SPI.obj: ../SPI.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=eabi -O2 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="SPI.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

debug.obj: ../debug.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=eabi -O2 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="debug.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.cpp $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=eabi -O2 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


