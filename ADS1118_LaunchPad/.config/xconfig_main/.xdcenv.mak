#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/grace_2_00_01_65/packages;C:/ti/ccsv5/ccs_base;C:/ti/msp430/MSP430ware_1_30_00_15/packages;C:/4_Embed_software/ADS1118_LaunchPad/.config
override XDCROOT = C:/ti/xdctools_3_24_05_48
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/grace_2_00_01_65/packages;C:/ti/ccsv5/ccs_base;C:/ti/msp430/MSP430ware_1_30_00_15/packages;C:/4_Embed_software/ADS1118_LaunchPad/.config;C:/ti/xdctools_3_24_05_48/packages;..
HOSTOS = Windows
endif
