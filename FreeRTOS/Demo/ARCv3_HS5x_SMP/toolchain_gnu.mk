ifeq ($(DEBUG), 1)
	CDEBUG_OPTION := -g -g3 -gdwarf-2
endif

ifeq ($(MAP), 1)
	LMAP_OPTION = -Wl,-M,-Map=$(APPL_FULL_NAME).map
endif

ifdef HEAPSZ
	HEAP_DEFINES := -D_HEAPSIZE=$(strip $(HEAPSZ))
else
	HEAP_DEFINES := -D_HEAPSIZE=$(strip $(DEFAULT_HEAPSZ))
endif

ifdef STACKSZ
	STACK_DEFINES := -D_STACKSIZE=$(strip $(STACKSZ))
else
	STACK_DEFINES := -D_STACKSIZE=$(strip $(DEFAULT_STACKSZ))
endif

TOOLCHAIN_DEFINES += $(HEAP_DEFINES) $(STACK_DEFINES) -D__GNU__

ifeq ($(ARC_CPU), hs5x)
	NSIMDRV_OPT = -propsfile nsim_hs5x.props
else
  ## ARC_CPU == arcem
	NSIMDRV_OPT = -propsfile nsim.props
endif

DBG_HW_FLAGS += -ex "target remote localhost:1234" -ex "load"

ifeq ($(ARC_CPU), hs5x)
	CCORE_OPT_GNU += -mcpu=hs5x -mcode-density -mdiv-rem \
		--param l1-cache-size=16384 --param l1-cache-line-size=32
else
  ## ARC_CPU == arcem
	CCORE_OPT_GNU += -mcpu=em4_dmips -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm \
		-mmpy-option=6 -mbarrel-shifter --param l1-cache-size=16384 --param l1-cache-line-size=32
endif

ACORE_OPT_GNU += $(CCORE_OPT_GNU)

LCORE_OPT_GNU += $(CCORE_OPT_GNU)
##
# define tools
##
GNU_TOOLCHAIN_PREFIX := $(strip $(GNU_TOOLPATH))

ifneq ($(GNU_TOOLCHAIN_PREFIX), )
GNU_TOOLCHAIN_PREFIX := $(wildcard $(GNU_TOOLCHAIN_PREFIX))
endif

## GNU TOOLCHAIN TOOLS NAME DEFINITIONS ##
ifeq ($(ARC_CPU), hs5x)
	CC	= arc64-elf-gcc
	LD	= arc64-elf-gcc
	DBG	?= arc64-elf-gdb
else
  ## ARC_CPU == arcem
	CC	= arc-elf32-gcc
	LD	= arc-elf32-gcc
	DBG	?= arc-elf32-gdb
endif

	MAKE	= make

	NSIMDRV	= nsimdrv

##
#   toolchain flags
##
libnsim = $(shell $(CC) -print-file-name=libnsim.a)
ifeq ($(libnsim),libnsim.a)
	# File doens't exists - old newlib.
	TOOLCHAIN_DEFINES += -U_HAVE_LIBGLOSS_
else
	TOOLCHAIN_DEFINES += -D_HAVE_LIBGLOSS_
endif

##
#   build options
##
	## Common Options
	MKDEP_OPT	= -MMD -MT $@ -MF $@.d

ifeq ($(ARC_CPU), hs5x)
	COMMON_COMPILE_OPT = -ffunction-sections -fdata-sections \
		$(OPT_OLEVEL) $(CDEBUG_OPTION) $(ALL_DEFINES) $(ALL_INCLUDES) $(MKDEP_OPT)
else
  ## ARC_CPU == arcem
	COMMON_COMPILE_OPT = -ffunction-sections -fdata-sections -mno-sdata \
		$(OPT_OLEVEL) $(CDEBUG_OPTION) $(ALL_DEFINES) $(ALL_INCLUDES) $(MKDEP_OPT)
endif

	## C/ASM/LINK Options
	COMPILE_OPT	+= $(CCORE_OPT_GNU)   $(ADT_COPT)   $(COMMON_COMPILE_OPT) -std=gnu99
	ASM_OPT		+= $(ACORE_OPT_GNU)   $(ADT_AOPT)   $(COMMON_COMPILE_OPT) -x assembler-with-cpp

ifeq ($(ARC_CPU), hs5x)
	LINK_OPT	+= $(LCORE_OPT_GNU)   $(ADT_LOPT) -Wl,--gc-sections \
		-nostartfiles $(LMAP_OPTION) -lm -Wl,--script=$(APPL_LINK_FILE)
else
  ## ARC_CPU == arcem
	LINK_OPT	+= $(LCORE_OPT_GNU)   $(ADT_LOPT) -Wl,--gc-sections \
		-mno-sdata -nostartfiles $(LMAP_OPTION) -lm -Wl,--script=$(APPL_LINK_FILE)
endif

	## Link File Generation Options
	LINK_FILE_OPT	+= -x assembler-with-cpp $(ALL_INCLUDES) -E -P -nostdinc -undef -D__GNU__
	LINK_FILE_DEPOPT = $(LINK_FILE_OPT) -DENABLE_GENERATE_DEPENDCY_FILE $(MKDEP_OPT)

	LD_START_GROUPLIB	= -Wl,--start-group
	LD_SYSTEMLIBS		= -lm -lc -lgcc
	LD_END_GROUPLIB		= -Wl,--end-group
