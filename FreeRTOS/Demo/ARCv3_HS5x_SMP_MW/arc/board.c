/*
 * Copyright (c) 2024 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "arc/arc.h"
#include "arc/arc_timer.h"
#include "arc/arc_exception.h"
#include "arc/arconnect.h"
#include "board.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/** board timer interrupt reset count */
static uint32_t cyc_hz_count = (BOARD_CPU_CLOCK / BOARD_SYS_TIMER_HZ);

/** board timer counter in timer interrupt */
static volatile uint64_t gl_sys_hz_cnt = 0;
/** board 1ms counter */
static volatile uint32_t gl_ms_cnt = 0;

#define HZ_COUNT_CONV(precision, base)  ((precision) / (base))

extern void __mw_run_tls_dtor();

void task_end_hook( void * pxTCB )
{
	TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

	if( task2free != NULL )
	{
		void * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

		if( tls )
		{
			__mw_run_tls_dtor();
			vPortFree( tls );
			vTaskSetThreadLocalStoragePointer( task2free, 0, NULL );
		}
	}
}

/** This function is defined in arc_freertos_exceptions.c, it can be blank in this demo */
void gnu_printf_setup(void)
{
}

/**
 * @brief Board bare-metal timer interrupt.
 *  Interrupt frequency is based on the defined @ref BOARD_SYS_TIMER_HZ
 */
static void board_timer_isr(void *ptr)
{
	arc_timer_int_clear(BOARD_SYS_TIMER_ID);

	board_timer_update(BOARD_SYS_TIMER_HZ);
}

/**
 * @brief Initialise bare-metal board timer and interrupt
 * @details
 * This function is called in @ref board_init, and
 * it initializes the 1-MS timer interrupt for bare-metal mode
 */
static void board_timer_init(void)
{
	if (arc_timer_present(BOARD_SYS_TIMER_ID)) {
		int_disable(BOARD_SYS_TIMER_INTNO);                                                     /* disable first then enable */
		int_handler_install(BOARD_SYS_TIMER_INTNO, board_timer_isr);
		arc_timer_start(BOARD_SYS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc_hz_count);       /* start 1ms timer interrupt */

		int_enable(BOARD_SYS_TIMER_INTNO);
	}
}

#define MIN_CALC(x, y)          (((x) < (y))?(x):(y))
/* Note: Task size in unit of StackType_t */
/* Note: Stack size should be small than 65536, since the stack size unit is uint16_t */
#define MIN_STACKSZ(size)       (MIN_CALC(size, configTOTAL_HEAP_SIZE) / sizeof(StackType_t))
#define TASK_STACK_SIZE_MAIN    MIN_STACKSZ(4096)
#define TASK_PRI_MAIN           1       /* Main task priority */

static TaskHandle_t task_handle_main;

/* exception stacks for each core */
#define EXC_STACKSIZE 2048
char exc_stacks[EXC_STACKSIZE*configNUMBER_OF_CORES];
char *core_exc_stack[configNUMBER_OF_CORES];

static void task_main(void)
{
	main();
	while (1) {
		vTaskSuspend(NULL);
	}
}

static void wait_for_irq(void)
{
	arc_unlock();
	while (true) {}
}

__attribute__((weak)) void platform_main(void)
{
	os_hal_exc_init();

	xTaskCreate(
		(TaskFunction_t) task_main, "main", TASK_STACK_SIZE_MAIN,
		NULL, TASK_PRI_MAIN, &task_handle_main
	);

	// vTaskStartScheduler() Will not return unless a task calls vTaskEndScheduler
	vTaskStartScheduler();
}

__attribute__((weak)) void board_main(void)
{
	/* init core level interrupt & exception management */
	exc_int_init();

	/* init inter-core interrupt */
	int_handler_install(ARCONNECT_INTRPT_LINE, vPortArconnectIciHandler);
	int_enable(ARCONNECT_INTRPT_LINE);

	/* necessary board level init */
	arc_timer_init();

	/* Initialise spinlocks to no owners */
	vPortInitSpinLock();

	uint32_t arcId = arconnect_get_core_id();

	if (arcId == 0) {
		/* Only one core starts timer for vKernelTick and starts the Task Scheduler */
		/* Initialise bare-metal board timer and interrupt */
		board_timer_init();

		/* Start FreeRTOS task scheduler */
		/* platform (e.g RTOS, baremetal) level init */
		platform_main();
	} else {
		/* Other cores wait until interrupted by the FreeRTOS task scheduler */
		wait_for_irq();
	}
}

/**
 * @brief Update timer counter and other MS period operation
 * in cycling interrupt and must be called periodically.
 * @param precision interrupt-period precision in Hz
 */
void board_timer_update(uint32_t precision)
{
	static uint32_t sys_hz_update = 0;
	static uint32_t sys_ms_update = 0;
	uint32_t hz_conv = 0;

	/** count sys hz */
	hz_conv = HZ_COUNT_CONV(precision, BOARD_SYS_TIMER_HZ);
	sys_hz_update++;
	if (sys_hz_update >= hz_conv) {
		sys_hz_update = 0;
		gl_sys_hz_cnt++;
	}

	/** count ms */
	hz_conv = HZ_COUNT_CONV(precision, BOARD_SYS_TIMER_MS_HZ);
	sys_ms_update++;
	if (sys_ms_update >= hz_conv) {
		sys_ms_update = 0;
		gl_ms_cnt++;
	}
}