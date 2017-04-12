#/*
#    FreeRTOS V9.0.1 - Copyright (C) 2017 Real Time Engineers Ltd.
#
#
#    ***************************************************************************
#     *                                                                       *
#     *    FreeRTOS tutorial books are available in pdf and paperback.        *
#     *    Complete, revised, and edited pdf reference manuals are also       *
#     *    available.                                                         *
#     *                                                                       *
#     *    Purchasing FreeRTOS documentation will not only help you, by       *
#     *    ensuring you get running as quickly as possible and with an        *
#     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
#     *    the FreeRTOS project to continue with its mission of providing     *
#     *    professional grade, cross platform, de facto standard solutions    *
#     *    for microcontrollers - completely free of charge!                  *
#     *                                                                       *
#     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
#     *                                                                       *
#     *    Thank you for using FreeRTOS, and thank you for your support!      *
#     *                                                                       *
#    ***************************************************************************
#
#
#    This file is part of the FreeRTOS distribution.
#
#    FreeRTOS is free software; you can redistribute it and/or modify it under
#    the terms of the GNU General Public License (version 2) as published by the
#    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
#    >>>NOTE<<< The modification to the GPL is included to allow you to
#    distribute a combined work that includes FreeRTOS without being obliged to
#    provide the source code for proprietary components outside of the FreeRTOS
#    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
#    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#    more details. You should have received a copy of the GNU General Public
#    License and the FreeRTOS license exception along with FreeRTOS; if not it
#    can be viewed here: http://www.freertos.org/a00114.html and also obtained
#    by writing to Richard Barry, contact details for whom are available on the
#    FreeRTOS WEB site.
#
#    1 tab == 4 spaces!
#
#    http://www.FreeRTOS.org - Documentation, latest information, license and
#    contact details.
#
#    http://www.SafeRTOS.com - A version that is certified for use in safety
#    critical systems.
#
#    http://www.OpenRTOS.com - Commercial support, development, porting,
#    licensing and training services.
#*/
## Small Functions ##
get_csrcs = $(foreach subdir, $(1), $(wildcard $(subdir)/*.c $(subdir)/*.C))
get_asmsrcs = $(foreach subdir, $(1), $(wildcard $(subdir)/*.s $(subdir)/*.S))
get_cxxsrcs = $(foreach subdir, $(1), $(wildcard $(subdir)/*.cpp $(subdir)/*.CPP))
## MAKEFILE COMPILE MESSAGE CONTROL ##
ECHO=echo
ifeq ($(V),1)
	Q=
else
	Q=@
endif

## Suppress All Message ##
ifeq ($(SILENT), 1)
	TRACE_CREATE_DIR	=
	TRACE_COMPILE		=
	TRACE_ASSEMBLE		=
	TRACE_LINK		=
	TRACE_ARCHIVE		=
	TRACE_GEN_LINKFILE	=
	## Overwrite Q Value set by V option ##
	override Q=@
else
	TRACE_CREATE_DIR	= @$(ECHO) "Creating Directory    : " $(@D)
	TRACE_COMPILE		= @$(ECHO) "Compiling             : " $<
	TRACE_ASSEMBLE		= @$(ECHO) "Assembling            : " $<
	TRACE_LINK		= @$(ECHO) "Linking               : " $@
	TRACE_ARCHIVE		= @$(ECHO) "Archiving             : " $@
	TRACE_GEN_LINKFILE	= @$(ECHO) "Generating Linkfile   : " $@
endif
###

APPL_FULL_NAME = RTOS_Demo
###
# Compiler Settings
###
CC=ccac
OBJCOPY=elf2bin
DUMP=elfdumpac
AR=arac
SIZE=sizeac
DBG=mdb

###
# Configurations need to be changed according to your environment
###
DEBUG = 1
EMBARC_BSP_ROOT = ../Common/drivers/Synopsys/embARC_BSP
FREERTOS_KERNEL_ROOT = ../../Source
FREERTOS_DEMO_COMMON_ROOT = ../Common
ARC_CORE_CONFIG_DIR = CoreConfig/23_ARCEM11D

COMPILE_OPT_ARGFILE = $(ARC_CORE_CONFIG_DIR)/ccac.arg
APP_LINK_FILE = $(ARC_CORE_CONFIG_DIR)/arc_core.ld

###
# embARC EMSK BSP source directories configuration
###
EMBARC_EMSK_BSP_ROOT = $(EMBARC_BSP_ROOT)/board/emsk

EMBARC_EMSK_BSP_CSRC_DIRS = $(EMBARC_EMSK_BSP_ROOT)/common \
			$(EMBARC_EMSK_BSP_ROOT)/gpio $(EMBARC_EMSK_BSP_ROOT)/uart $(EMBARC_EMSK_BSP_ROOT)/iic

EMBARC_BSP_CSRC_DIRS = $(EMBARC_BSP_ROOT)/arc/startup $(EMBARC_BSP_ROOT)/arc \
			$(EMBARC_BSP_ROOT)/board $(EMBARC_EMSK_BSP_CSRC_DIRS) \
			$(EMBARC_BSP_ROOT)/device/designware/gpio \
			$(EMBARC_BSP_ROOT)/device/designware/iic  \
			$(EMBARC_BSP_ROOT)/device/designware/uart \
			$(EMBARC_BSP_ROOT)/common


EMBARC_BSP_ASMSRC_DIRS = $(EMBARC_BSP_ROOT)/arc/startup $(EMBARC_BSP_ROOT)/arc
EMBARC_BSP_INC_DIRS = $(EMBARC_BSP_ROOT)

###
# embARC EMSK BSP c/asm source files configuration
##
EMBARC_EMSK_BSP_CSRCS = $(call get_csrcs, $(EMBARC_BSP_CSRC_DIRS))
EMBARC_EMSK_BSP_ASMSRCS = $(call get_asmsrcs, $(EMBARC_BSP_ASMSRC_DIRS))

###
# C/ASM source files
###
FREERTOS_KERNEL_CSRCS = $(FREERTOS_KERNEL_ROOT)/croutine.c \
		$(FREERTOS_KERNEL_ROOT)/event_groups.c \
		$(FREERTOS_KERNEL_ROOT)/list.c \
		$(FREERTOS_KERNEL_ROOT)/queue.c \
		$(FREERTOS_KERNEL_ROOT)/tasks.c \
		$(FREERTOS_KERNEL_ROOT)/timers.c \
		$(FREERTOS_KERNEL_ROOT)/portable/MemMang/heap_2.c \
		$(FREERTOS_KERNEL_ROOT)/portable/Synopsys/ARC/port.c

FREERTOS_KERNEL_ASMSRCS = $(FREERTOS_KERNEL_ROOT)/portable/Synopsys/ARC/arc_support.S

FREERTOS_KERNEL_INC_DIRS = $(FREERTOS_KERNEL_ROOT)/include \
		$(FREERTOS_KERNEL_ROOT)/portable/Synopsys/ARC

###
# Demo C Source files
###
FREERTOS_DEMO_C_SRCS = $(FREERTOS_DEMO_COMMON_ROOT)/Minimal/integer.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/flash.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/PollQ.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/comtest.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/flop.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/semtest.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/dynamic.c \
			$(FREERTOS_DEMO_COMMON_ROOT)/Minimal/BlockQ.c

FREERTOS_DEMO_INC_DIRS = $(FREERTOS_DEMO_COMMON_ROOT)/include

###
# All C/ASM source files
###
ALL_C_SRCS = main.c Serial/serial.c Serial/serialISR.c ParTest/ParTest.c \
		$(FREERTOS_DEMO_C_SRCS) $(FREERTOS_KERNEL_CSRCS) \
		$(EMBARC_EMSK_BSP_CSRCS)

ALL_ASM_SRCS = $(FREERTOS_KERNEL_ASMSRCS) $(EMBARC_EMSK_BSP_ASMSRCS)
ALL_INC_DIRS = . $(ARC_CORE_CONFIG_DIR) $(EMBARC_BSP_INC_DIRS) \
		$(FREERTOS_DEMO_INC_DIRS) $(FREERTOS_KERNEL_INC_DIRS)

###
# Compiler Options
###

ifeq ($(DEBUG), 1)
	OS_FREERTOS_DEFINES += -DINCLUDE_uxTaskGetStackHighWaterMark=1
	OS_FREERTOS_DEFINES += -DconfigGENERATE_RUN_TIME_STATS=1
	COMMON_COMPILE_OPT += -g
endif

ALL_INCLUDES = $(foreach dir,$(ALL_INC_DIRS),-I$(dir))
ALL_DEFINES = -DMID_COMMON $(OS_FREERTOS_DEFINES)

LMAP_OPTION = -Hldopt=-Coutput=$(APPL_FULL_NAME).map -Hldopt=-Csections -Hldopt=-Ccrossfunc -Hldopt=-Csize -zstdout
MKDEP_OPT = -MMD -MT $@ -MF $@.d
COMMON_COMPILE_OPT += -O2 -Hnoccm -Hnosdata -Wincompatible-pointer-types -Hnocopyr $(ALL_INCLUDES) $(MKDEP_OPT) $(ALL_DEFINES)

CFLAGS = @$(COMPILE_OPT_ARGFILE) $(COMMON_COMPILE_OPT) -Hnocplus
CXXFLAGS = @$(COMPILE_OPT_ARGFILE) $(COMMON_COMPILE_OPT)
ASFLAGS = @$(COMPILE_OPT_ARGFILE) $(COMMON_COMPILE_OPT) -Hasmcpp
LDFLAGS = @$(COMPILE_OPT_ARGFILE) -Hnocopyr -Hnosdata -Hnocrt \
		$(LMAP_OPTION) $(APP_LINK_FILE)
LDFLAGS_LIBS = -Hldopt=-Bgrouplib

DBG_HW_FLAGS = -nooptions -nogoifmain -toggle=include_local_symbols=1 -OS=FreeRTOS -digilent

## Run target options
ifeq ($(MAKECMDGOALS),run)
DBG_HW_FLAGS += -run
endif
#
# Define all object files.
#
COBJS = $(addsuffix .o, $(ALL_C_SRCS))
CXXOBJS = $(addsuffix .o, $(ALL_CXX_SRCS))
ASMOBJS = $(addsuffix .o, $(ALL_ASM_SRCS))
ALLOBJS = $(ASMOBJS) $(COBJS) $(CXXOBJS)
ALLDEPS = $(ALLOBJS:.o=.o.d)

.PHONY : all bin hex size clean run gui

all : $(APPL_FULL_NAME).elf

bin : $(APPL_FULL_NAME).bin

hex : $(APPL_FULL_NAME).hex

size : $(APPL_FULL_NAME).elf
	@$(ECHO) "Print Application Program Size"
	$(Q)$(SIZE) $(SIZE_OPT) $<

$(APPL_FULL_NAME).hex : $(APPL_FULL_NAME).elf
	@$(ECHO) "Generating Intel Hex File $@"
	$(Q)$(OBJCOPY) -O ihex $< $@

$(APPL_FULL_NAME).bin : $(APPL_FULL_NAME).elf
	@$(ECHO) "Generating Binary $@"
	$(Q)$(OBJCOPY) -O binary $< $@

$(APPL_FULL_NAME).elf : $(ALLOBJS) Makefile
	$(TRACE_LINK)
	$(Q)$(CC) $(LDFLAGS) $(ALLOBJS) $(LDFLAGS_LIBS) -o $@

$(COBJS) : %.o : %  Makefile
	$(TRACE_COMPILE)
	$(Q)$(CC) -c $(CFLAGS) $< -o $@

$(CXXOBJS) : %.o : %  Makefile
	$(TRACE_COMPILE)
	$(Q)$(CC) -c $(CXXFLAGS) $< -o $@

$(ASMOBJS) : %.o : %  Makefile
	$(TRACE_ASSEMBLE)
	$(Q)$(CC) -c $(ASFLAGS) $< -o $@

run : $(APPL_FULL_NAME).elf
	@$(ECHO) "Download & Run $<"
	$(DBG) $(DBG_HW_FLAGS) $<

gui : $(APPL_FULL_NAME).elf
	@$(ECHO) "Download & Debug $<"
	$(DBG) $(DBG_HW_FLAGS) $<

clean :
	@$(ECHO) "Clean all object files and dependency files"
	-$(Q)rm -rf $(ALLOBJS)
	-$(Q)rm -rf $(ALLDEPS)
	-$(Q)rm -rf $(APPL_FULL_NAME).elf $(APPL_FULL_NAME).map
	-$(Q)rm -rf openocd.log .sc.project *.log
	@$(ECHO) "Clean finished"

-include $(ALLDEPS)