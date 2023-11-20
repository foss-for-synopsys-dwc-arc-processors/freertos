TOOLCHAIN ?= mw

APPL_FULL_NAME ?= $(BUILD_DIR)/RTOSDemo

OPT_OLEVEL = -O2

DEBUG ?= 1

HEAPSZ ?= 8192

STACKSZ ?= 2048

MAP ?= 1

include ./toolchain_$(TOOLCHAIN).mk

ALL_DEFINES += -DPLATFORM_EMBARC -DBOARD_NSIM -DCPU_ARC -DFREERTOS_HEAP_SEL=2 \
	-DHW_VERSION=10 -DconfigGENERATE_RUN_TIME_STATS=1 -D_NSIM_ \
	-DconfigNUM_THREAD_LOCAL_STORAGE_POINTERS=1 -DconfigUSE_RECURSIVE_MUTEXES=1 $(TOOLCHAIN_DEFINES)

ALL_INCLUDES += 	-I . -I arc/ -I ../Common/include \
	-I $(RTOS_SOURCE_DIR)/include \
	-I $(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS

LINKER_SCRIPT_FILE ?= linker_template_$(TOOLCHAIN).ld
APPL_LINK_FILE = $(BUILD_DIR)/linker_$(TOOLCHAIN).ldf

BUILD_DIR       = build
RTOS_SOURCE_DIR = $(abspath ../../Source)
DEMO_SOURCE_DIR = $(abspath ../Common/Minimal)

# SRCS = main.c arc/arc_exception.c arc/board.c arc/arc_timer.c ns16550-virt.c printf-stdarg.c
SRCS = main.c arc/board.c ns16550-virt.c printf-stdarg.c \
	$(RTOS_SOURCE_DIR)/event_groups.c \
	$(RTOS_SOURCE_DIR)/list.c \
	$(RTOS_SOURCE_DIR)/queue.c \
	$(RTOS_SOURCE_DIR)/stream_buffer.c \
	$(RTOS_SOURCE_DIR)/tasks.c \
	$(RTOS_SOURCE_DIR)/timers.c \
	$(RTOS_SOURCE_DIR)/portable/MemMang/heap_4.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS/port.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS/arc_freertos_exceptions.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS/arc/arc_exception.c \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS/arc/arc_timer.c

ASMS = arc_startup.s \
	$(RTOS_SOURCE_DIR)/portable/ThirdParty/GCC/ARC_EM_HS/arc_support.s

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

debug : $(APPL_FULL_NAME).elf
	$(DBG) $(DBG_HW_FLAGS) $<

clean:
	rm -rf $(BUILD_DIR) ? .sc.project

nsim :
	nsimdrv -gdb -port 1234 -p nsim_emt=1 $(NSIMDRV_OPT)

qemu :
	qemu-system-arc -cpu arcem -M virt -m 8M -nographic -net none -kernel build/RTOSDemo.elf -chardev stdio,id=con,mux=on -serial chardev:con -mon chardev=con,mode=readline \
	-global cpu.firq=false -global cpu.num-irqlevels=15 -global cpu.num-irq=25 -global cpu.ext-irq=20 -global cpu.freq_hz=1000000 -global cpu.timer0=true -global cpu.timer1=true -s -S
