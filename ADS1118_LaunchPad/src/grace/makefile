# optional compiler flags
CCOPTS ?= --symdebug:dwarf --optimize_with_debug -qq -pdsw225 

# required C preprocessor flags
#    compiler   headers: "C:/ti/ccsv5/tools/compiler/msp430_4.1.2/include"
#    device     headers: "C:/ti/ccsv5/ccs_base/msp430/include"
#    Grace      headers: "C:/ti/grace_2_00_01_65/packages" 
#    MSP430ware headers: "C:/ti/msp430/MSP430ware_1_30_00_15/packages/../"
CPPFLAGS = -D__MSP430G2553__ -I "C:/ti/ccsv5/tools/compiler/msp430_4.1.2/include" -I "C:/ti/grace_2_00_01_65/packages"  -I "C:/ti/ccsv5/ccs_base/msp430/include" -I "C:/ti/msp430/MSP430ware_1_30_00_15/packages/../"

# the compiler and archiver commands
CC = "C:/ti/ccsv5/tools/compiler/msp430_4.1.2/bin/cl430" --abi=eabi -c --obj_directory=objs/  -vmsp
AR = "C:/ti/ccsv5/tools/compiler/msp430_4.1.2/bin/ar430" rq
RM = cmd.exe /q /c del /f
MKDIR = mkdir

# create object sub-directory, if necessary
ifeq (,$(wildcard objs/))
    $(shell $(MKDIR) objs\)
endif

all: grace.lib

# pattern rule to compile .c source to an object file
objs/%.obj: %.c makefile
	@echo cle430 $< ...
	$(CC) $(CCOPTS) $(CPPFLAGS) "$<"

# rule to combine all objects into the grace.lib library
grace.lib: objs/Grace_init.obj objs/CSL_init.obj objs/GPIO_init.obj objs/BCSplus_init.obj objs/USCI_A0_init.obj objs/InterruptVectors_init.obj objs/USCI_B0_init.obj objs/System_init.obj objs/Timer1_A3_init.obj objs/Timer0_A3_init.obj objs/WDTplus_init.obj
	@ echo are430 $@ $< ...
	$(AR) $@ $^

# clean removes all generated files 
clean:
	-$(RM) grace.lib
	-$(RM) "objs\"*.obj

