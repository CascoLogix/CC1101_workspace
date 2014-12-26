################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.5/bin/cl430" -vmsp --abi=eabi -g --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/CC1101_workspace/ADS1118_LaunchPad/usr" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.5/include" --advice:power="all" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../main.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_24_05_48/xs" --xdcpath="c:/ti/grace_3_00_01_59/packages;c:/ti/ccsv6/ccs_base;C:/ti/msp430/MSP430ware_1_95_00_32/packages;" xdc.tools.configuro -o configPkg -t ti.targets.msp430.elf.MSP430 -p ti.platforms.msp430:MSP430G2553 -r debug -c "c:/ti/ccsv6/tools/compiler/msp430_4.3.5" --compileOptions "--symdebug:dwarf --optimize_with_debug" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


