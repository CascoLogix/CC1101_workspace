################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Components/nwk/nwk.obj: C:/ti/ccsv6/eclipse/DEV_ROOT/Components/simpliciti/nwk/nwk.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/bin/cl430" --cmd_file="C:/CC1101_workspace/Project/../Configuration/smpl_nwk_config.dat" --cmd_file="C:/CC1101_workspace/Project/../Configuration/End_Device/smpl_config.dat"  -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="C:/Components/bsp" --include_path="C:/Components/bsp/boards/eZ430RF" --include_path="C:/Components/bsp/drivers" --include_path="C:/Components/mrfi" --include_path="C:/Components/simpliciti/nwk" --include_path="C:/Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/nwk/nwk.pp" --obj_directory="Components/nwk" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Components/nwk/nwk_QMgmt.obj: C:/ti/ccsv6/eclipse/DEV_ROOT/Components/simpliciti/nwk/nwk_QMgmt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/bin/cl430" --cmd_file="C:/CC1101_workspace/Project/../Configuration/smpl_nwk_config.dat" --cmd_file="C:/CC1101_workspace/Project/../Configuration/End_Device/smpl_config.dat"  -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="C:/Components/bsp" --include_path="C:/Components/bsp/boards/eZ430RF" --include_path="C:/Components/bsp/drivers" --include_path="C:/Components/mrfi" --include_path="C:/Components/simpliciti/nwk" --include_path="C:/Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/nwk/nwk_QMgmt.pp" --obj_directory="Components/nwk" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Components/nwk/nwk_api.obj: C:/ti/ccsv6/eclipse/DEV_ROOT/Components/simpliciti/nwk/nwk_api.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/bin/cl430" --cmd_file="C:/CC1101_workspace/Project/../Configuration/smpl_nwk_config.dat" --cmd_file="C:/CC1101_workspace/Project/../Configuration/End_Device/smpl_config.dat"  -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="C:/Components/bsp" --include_path="C:/Components/bsp/boards/eZ430RF" --include_path="C:/Components/bsp/drivers" --include_path="C:/Components/mrfi" --include_path="C:/Components/simpliciti/nwk" --include_path="C:/Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/nwk/nwk_api.pp" --obj_directory="Components/nwk" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Components/nwk/nwk_frame.obj: C:/ti/ccsv6/eclipse/DEV_ROOT/Components/simpliciti/nwk/nwk_frame.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/bin/cl430" --cmd_file="C:/CC1101_workspace/Project/../Configuration/smpl_nwk_config.dat" --cmd_file="C:/CC1101_workspace/Project/../Configuration/End_Device/smpl_config.dat"  -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="C:/Components/bsp" --include_path="C:/Components/bsp/boards/eZ430RF" --include_path="C:/Components/bsp/drivers" --include_path="C:/Components/mrfi" --include_path="C:/Components/simpliciti/nwk" --include_path="C:/Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/nwk/nwk_frame.pp" --obj_directory="Components/nwk" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Components/nwk/nwk_globals.obj: C:/ti/ccsv6/eclipse/DEV_ROOT/Components/simpliciti/nwk/nwk_globals.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/bin/cl430" --cmd_file="C:/CC1101_workspace/Project/../Configuration/smpl_nwk_config.dat" --cmd_file="C:/CC1101_workspace/Project/../Configuration/End_Device/smpl_config.dat"  -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="c:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.2/include" --include_path="C:/Components/bsp" --include_path="C:/Components/bsp/boards/eZ430RF" --include_path="C:/Components/bsp/drivers" --include_path="C:/Components/mrfi" --include_path="C:/Components/simpliciti/nwk" --include_path="C:/Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/nwk/nwk_globals.pp" --obj_directory="Components/nwk" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


