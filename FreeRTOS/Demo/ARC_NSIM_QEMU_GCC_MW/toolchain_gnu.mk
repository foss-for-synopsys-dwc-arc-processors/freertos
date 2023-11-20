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

NSIMDRV_OPT = -propsfile nsim.props

DBG_HW_FLAGS += -ex "target remote localhost:1234" -ex "load"

CCORE_OPT_GNU += -mcpu=em4_dmips -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm \
	-mmpy-option=6 -mbarrel-shifter --param l1-cache-size=16384 --param l1-cache-line-size=32

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
	CC	= arc-elf32-gcc
	LD	= arc-elf32-gcc

	MAKE	= make
	DBG	?= arc-elf32-gdb

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
	COMMON_COMPILE_OPT = -ffunction-sections -fdata-sections -mno-sdata \
			$(OPT_OLEVEL) $(CDEBUG_OPTION) $(ALL_DEFINES) $(ALL_INCLUDES) $(MKDEP_OPT)

	## C/ASM/LINK Options
	COMPILE_OPT	+= $(CCORE_OPT_GNU)   $(ADT_COPT)   $(COMMON_COMPILE_OPT) -std=gnu99
	ASM_OPT		+= $(ACORE_OPT_GNU)   $(ADT_AOPT)   $(COMMON_COMPILE_OPT) -x assembler-with-cpp
	LINK_OPT	+= $(LCORE_OPT_GNU)   $(ADT_LOPT) -Wl,--gc-sections \
				-mno-sdata -nostartfiles $(LMAP_OPTION) -lm -Wl,--script=$(APPL_LINK_FILE)

	## Link File Generation Options
	LINK_FILE_OPT	+= -x assembler-with-cpp $(ALL_INCLUDES) -E -P -nostdinc -undef -D__GNU__
	LINK_FILE_DEPOPT = $(LINK_FILE_OPT) -DENABLE_GENERATE_DEPENDCY_FILE $(MKDEP_OPT)

	LD_START_GROUPLIB	= -Wl,--start-group
	LD_SYSTEMLIBS		= -lm -lc -lgcc
	LD_END_GROUPLIB		= -Wl,--end-group
