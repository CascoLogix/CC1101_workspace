## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e430 linker.cmd \
  package/cfg/main_pe430.oe430 \

linker.cmd: package/cfg/main_pe430.xdl
	$(SED) 's"^\"\(package/cfg/main_pe430cfg.cmd\)\"$""\"C:/4_Embed_software/ADS1118_LaunchPad/Debug/configPkg/\1\""' package/cfg/main_pe430.xdl > $@
