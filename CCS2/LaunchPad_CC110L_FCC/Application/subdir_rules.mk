################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Application/Application.obj: C:/CC1101_workspace/src/Application/Application.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/Application.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/Callback.obj: C:/CC1101_workspace/src/Application/Callback.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/Callback.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/CommandInterface.obj: C:/CC1101_workspace/src/Application/CommandInterface.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/CommandInterface.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/Protocol.obj: C:/CC1101_workspace/src/Application/Protocol.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/Protocol.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/RadioOperation.obj: C:/CC1101_workspace/src/Application/RadioOperation.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/RadioOperation.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/main.obj: C:/CC1101_workspace/src/Application/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/bin/cl430" -vmsp --abi=coffabi -O4 --opt_for_speed=0 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/MSP430_4.2.2/include" --include_path="C:/CC1101_workspace/src/Library" --include_path="C:/CC1101_workspace/src/Framework" -g --define=__MSP430G2553__ --define=__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE --define=__RADIO_A110LR09 --define=__RADIO_CERTIFICATION_FCC --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="Application/main.pp" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


