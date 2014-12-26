# invoke SourceDir generated makefile for main.pe430
main.pe430: .libraries,main.pe430
.libraries,main.pe430: package/cfg/main_pe430.xdl
	$(MAKE) -f C:\CC1101_workspace\LaunchPad_MSP430G2553_UART_Test/src/makefile.libs

clean::
	$(MAKE) -f C:\CC1101_workspace\LaunchPad_MSP430G2553_UART_Test/src/makefile.libs clean

