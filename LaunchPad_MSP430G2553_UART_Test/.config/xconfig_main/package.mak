#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = xconfig_main
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
C:/ti/xdctools_3_30_03_47_core/packages/xdc/utils.js:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/utils.js
C:/ti/xdctools_3_30_03_47_core/packages/xdc/xdc.tci:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/xdc.tci
C:/ti/xdctools_3_30_03_47_core/packages/xdc/template.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/template.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/om2.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/om2.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/xmlgen.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/xmlgen.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/xmlgen2.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/xmlgen2.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/Warnings.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/Warnings.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/IPackage.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/IPackage.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/package.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/package.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/global/Clock.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/global/Clock.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/global/Trace.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/global/Trace.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/bld.js:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/bld.js
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/BuildEnvironment.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/PackageContents.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/PackageContents.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/_gen.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/_gen.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Library.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Library.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Executable.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Executable.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Repository.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Repository.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Configuration.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Configuration.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Script.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Script.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Manifest.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Manifest.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Utils.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/Utils.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget2.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget2.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget3.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITarget3.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/ITargetFilter.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/package.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/bld/package.xs
package.mak: config.bld
C:/ti/grace_3_00_01_59/packages/ti/targets/ITarget.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/ITarget.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/C28_large.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/C28_large.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/C28_float.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/C28_float.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/package.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/package.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430X.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430X.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430X_small.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/MSP430X_small.xs
C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/package.xs:
package.mak: C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/package.xs
package.mak: package.bld
C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/compiler.opt.xdt
C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/io/File.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/io/File.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/io/package.xs:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/services/io/package.xs
C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/compiler.defs.xdt
C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: C:/ti/xdctools_3_30_03_47_core/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.msp430.elf.MSP430.rootDir ?= c:/ti/ccsv6/tools/compiler/msp430_4.3.5
ti.targets.msp430.elf.packageBase ?= C:/ti/grace_3_00_01_59/packages/ti/targets/msp430/elf/
.PRECIOUS: $(XDCCFGDIR)/%.oe430
.PHONY: all,e430 .dlls,e430 .executables,e430 test,e430
all,e430: .executables,e430
.executables,e430: .libraries,e430
.executables,e430: .dlls,e430
.dlls,e430: .libraries,e430
.libraries,e430: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,e430
	@$(ECHO) xdc .executables,e430
	@$(ECHO) xdc .libraries,e430
	@$(ECHO) xdc .dlls,e430


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_xconfig_main.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package xconfig_main" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,e430 .dlls: main.pe430

-include package/cfg/main_pe430.mak
-include package/cfg/main_pe430.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/main_pe430.dep
endif
main.pe430: package/cfg/main_pe430.xdl
	@


ifeq (,$(wildcard .libraries,e430))
main.pe430 package/cfg/main_pe430.c: .libraries,e430
endif

package/cfg/main_pe430.c package/cfg/main_pe430.h package/cfg/main_pe430.xdl: override _PROG_NAME := main.xe430
package/cfg/main_pe430.c package/cfg/main_pe430.xdl: override _PROG_XSOPTS = -Dxdc.cfg.tsort.policy=fast -Dxdc.cfg.gen.metadataFiles=false -Dxdc.cfg.SourceDir.verbose=7
package/cfg/main_pe430.c: package/cfg/main_pe430.cfg

clean:: clean,e430
	-$(RM) package/cfg/main_pe430.cfg
	-$(RM) package/cfg/main_pe430.dep
	-$(RM) package/cfg/main_pe430.c
	-$(RM) package/cfg/main_pe430.xdc.inc

clean,e430::
	-$(RM) main.pe430
.executables,e430 .executables: main.xe430

main.xe430: |main.pe430

-include package/cfg/main.xe430.mak
main.xe430: package/cfg/main_pe430.oe430 
	$(RM) $@
	@$(MSG) lnke430 $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.msp430.elf.MSP430.rootDir)/bin/lnk430 -w -q -u _c_int00 -fs $(XDCCFGDIR)$(dir $@).  -q -o $@ package/cfg/main_pe430.oe430   package/cfg/main_pe430.xdl  -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.msp430.elf.MSP430.rootDir)/lib/libc.a
	
main.xe430: export C_DIR=
main.xe430: PATH:=$(ti.targets.msp430.elf.MSP430.rootDir)/bin/;$(PATH)
main.xe430: Path:=$(ti.targets.msp430.elf.MSP430.rootDir)/bin/;$(PATH)

main.test test,e430 test: main.xe430.test

main.xe430.test:: main.xe430
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 main.xe430.test
else
	@$(MSG) running $<  ...
	$(call EXEC.main.xe430, ) 
endif

clean,e430::
	-$(RM) $(wildcard .tmp,main.xe430,*)


clean:: clean,e430

clean,e430::
	-$(RM) main.xe430
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
main_pe430.oe430,copy : package/cfg/main_pe430.oe430
main_pe430.se430,copy : package/cfg/main_pe430.se430

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg .interfaces $(XDCROOT)/packages/xdc/cfg/Main.xs
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,xconfig_main
xconfig_main.tar: package/package.bld.xml
xconfig_main.tar: package/build.cfg
xconfig_main.tar: package/package.xdc.inc
ifeq (,$(MK_NOGENDEPS))
-include package/rel/xconfig_main.tar.dep
endif
package/rel/xconfig_main/xconfig_main/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

xconfig_main.tar: package/rel/xconfig_main.xdc.inc package/rel/xconfig_main/xconfig_main/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/xconfig_main.xdc.inc,package/rel/xconfig_main.tar.dep)


release release,xconfig_main: all xconfig_main.tar
clean:: .clean
	-$(RM) xconfig_main.tar
	-$(RM) package/rel/xconfig_main.xdc.inc
	-$(RM) package/rel/xconfig_main.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
