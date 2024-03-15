TOOLCHAIN ?= mw

APPL_FULL_NAME ?= $(BUILD_DIR)/RTOSDemo

OPT_OLEVEL = -g

DEBUG ?= 1

HEAPSZ ?= 8192

STACKSZ ?= 2048

MAP ?= 1

include ./toolchain_$(TOOLCHAIN).mk

RTOS_SOURCE_DIR = $(abspath ../../Source)
# RTOS_SOURCE_DIR = $(abspath ../../../../FreeRTOS-Kernel)

ALL_DEFINES += -DPLATFORM_EMBARC -DBOARD_NSIM -DCPU_ARC -DFREERTOS_HEAP_SEL=2 \
	-DHW_VERSION=10 -DconfigGENERATE_RUN_TIME_STATS=1 -D_NSIM_ \
	-DconfigNUM_THREAD_LOCAL_STORAGE_POINTERS=1 -DconfigUSE_RECURSIVE_MUTEXES=1 $(TOOLCHAIN_DEFINES)

ALL_INCLUDES += 	-I . -I arc/ -I ../Common/include \
	-I $(RTOS_SOURCE_DIR)/include \
	-I $(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP

LINKER_SCRIPT_FILE ?= linker_template_$(TOOLCHAIN).ld
APPL_LINK_FILE = $(BUILD_DIR)/linker_$(TOOLCHAIN).ldf

BUILD_DIR       = build
DEMO_SOURCE_DIR = $(abspath ../Common/Minimal)

SRCS = main.c arc/board.c ns16550-virt.c printf-stdarg.c \
	$(RTOS_SOURCE_DIR)/event_groups.c \
	$(RTOS_SOURCE_DIR)/list.c \
	$(RTOS_SOURCE_DIR)/queue.c \
	$(RTOS_SOURCE_DIR)/stream_buffer.c \
	$(RTOS_SOURCE_DIR)/tasks.c \
	$(RTOS_SOURCE_DIR)/timers.c \
	$(RTOS_SOURCE_DIR)/portable/MemMang/heap_4.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/port.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/arc_freertos_exceptions.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/arc/arc_exception.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/arc/arc_timer.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/arc/arconnect.c

ASMS = arc_startup.s \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARCv3_HS5x_SMP/arc_support.s

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o) $(ASMS:%.s=$(BUILD_DIR)/%.o)

$(APPL_FULL_NAME).elf: $(OBJS) $(APPL_LINK_FILE)
	$(LD) $(LINK_OPT) $(OBJS) -o $@

$(APPL_LINK_FILE): $(LINKER_SCRIPT_FILE)
	$(CC) -c $(ALL_DEFINES) $(LINK_FILE_OPT) $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(COMPILE_OPT) $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(@D)
	$(CC) -c $(ASM_OPT) $< -o $@

debug: $(APPL_FULL_NAME).elf
	$(DBG) $(DBG_HW_FLAGS_CORE0) $<
	$(DBG) $(DBG_HW_FLAGS_CORE1) $<
	$(DBG) $(DBG_HW_FLAGS_CORE2) $<
	$(DBG) $(DBG_HW_FLAGS_CORE3) $<
	NSIM_MULTICORE=1 $(DBG) $(DBG_HW_FLAGS_4_CORES)

clean:
	rm -rf $(BUILD_DIR) ? .sc.project