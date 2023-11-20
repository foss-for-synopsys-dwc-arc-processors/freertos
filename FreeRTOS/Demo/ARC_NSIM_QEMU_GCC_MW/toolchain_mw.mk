ifeq ($(DEBUG), 1)
	CDEBUG_OPTION := -g
endif

ifeq ($(MAP), 1)
	LMAP_OPTION = -Hldopt=-Coutput=$(APPL_FULL_NAME).map -Hldopt=-Csections -Hldopt=-Ccrossfunc -Hldopt=-Csize -zstdout
endif

ifdef HEAPSZ
	HEAP_DEFINES := -D_HEAPSIZE=$(strip $(HEAPSZ))
else
	HEAP_DEFINES += -D_HEAPSIZE=$(strip $(DEFAULT_HEAPSZ))
endif

ifdef STACKSZ
	STACK_DEFINES := -D_STACKSIZE=$(strip $(STACKSZ))
else
	STACK_DEFINES += -D_STACKSIZE=$(strip $(DEFAULT_STACKSZ))
endif

TOOLCHAIN_DEFINES += $(HEAP_DEFINES) $(STACK_DEFINES) -D__MW__

DBG_HW_FLAGS += @mdb_arg.props

CCORE_OPT_MW += -arcv2em -core3 -HL -Xcode_density -Xdiv_rem=radix2 -Xswap -Xbitscan -Xmpy_option=mpyd -Xshift_assist \
	-Xbarrel_shifter -Xdsp2 -Xdsp_complex -Xdsp_divsqrt=radix2 -Xdsp_itu -Xdsp_accshift=full -Xagu_large -Xxy -Xfpus_div \
	-Xfpu_mac -Xfpuda -Xfpus_mpy_slow -Xfpus_div_slow -Xbitstream -Xtimer0 -Xtimer1 -Xstack_check -Hccm -Xdmac

ASM_OPT += $(CCORE_OPT_MW)

LCORE_OPT_MW += $(CCORE_OPT_MW)

##
# define tools
##
MW_TOOLCHAIN_PREFIX := $(strip $(MW_TOOLPATH))

ifneq ($(MW_TOOLCHAIN_PREFIX), )
MW_TOOLCHAIN_PREFIX := $(wildcard $(MW_TOOLCHAIN_PREFIX))
endif

## METAWARE TOOLCHAIN TOOLS NAME DEFINITIONS ##
	CC	= ccac
	LD   	= ccac

	MAKE	= gmake
	DBG	= mdb

	NSIMDRV	= nsimdrv

##
#   build options
##
	## Common Options
	MKDEP_OPT	= -MMD -MT $@ -MF $@.d
	### Disable small data and disable optimization for closely coupled memory (a Harvard architecture)
	COMMON_COMPILE_OPT = -Hnoccm -Hnosdata -Wincompatible-pointer-types -Hnocopyr -Hpurge -fdata-sections\
				$(OPT_OLEVEL) $(CDEBUG_OPTION) $(ALL_DEFINES) $(ALL_INCLUDES) $(MKDEP_OPT)

	## C/CPP/ASM/LINK Options
	COMPILE_OPT	+= $(CCORE_OPT_MW)   $(ADT_COPT)   $(COMMON_COMPILE_OPT) -Hnocplus
	ASM_OPT		+= $(ACORE_OPT_MW)   $(ADT_AOPT)   $(COMMON_COMPILE_OPT) -Hasmcpp
	LINK_OPT	+= $(LCORE_OPT_MW)   $(ADT_LOPT) -Hpurge\
				-Hnocopyr -Hnosdata -Hnocrt $(LMAP_OPTION) $(APPL_LINK_FILE)

	## Link File Generation Options
	LINK_FILE_OPT	+= -Hnocopyr -Hasmcpp -Hasext=ld,lcf,met -Hnoarcexlib -Hnoarcsimd -E -nostdsysteminc -undef -D__MW__ $(ALL_INCLUDES)
	LINK_FILE_DEPOPT = $(LINK_FILE_OPT) -DENABLE_GENERATE_DEPENDCY_FILE $(MKDEP_OPT)

	LD_START_GROUPLIB	= -Hldopt=-Bgrouplib
	LD_SYSTEMLIBS		=
	LD_END_GROUPLIB		=
