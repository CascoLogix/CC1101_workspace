################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Framework/Drivers/Timer/SoftwareTimer.obj: C:/CC1101_workspace/src/Framework/Drivers/Timer/SoftwareTimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Framework/Drivers/Timer/SoftwareTimer.pp" --obj_directory="Framework/Drivers/Timer" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


