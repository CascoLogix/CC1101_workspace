################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Framework/BSP/Boards/EZ430/EZ430.obj: C:/CC1101_workspace/src/Framework/BSP/Boards/EZ430/EZ430.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Framework/BSP/Boards/EZ430/EZ430.pp" --obj_directory="Framework/BSP/Boards/EZ430" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


