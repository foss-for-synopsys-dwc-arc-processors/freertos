/*
 * Copyright (c) 2022 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 *
 * @file
 * @ingroup	BOARD_COMMON
 * @brief	common board header file
 * @details
 * - This header file will contain board related settings.
 */

/**
 * @addtogroup BOARD_COMMON
 * @{
 */
#ifndef _BOARD_H_
#define _BOARD_H_
/**
 * @todo	add comments and documents to describe the macros
 * @note 	the following macros must use the same name, because
 *	they are used by middleware and other applications
 */
#include "FreeRTOS.h"
#include "croutine.h"
#include "event_groups.h"
#include "list.h"
#include "mpu_wrappers.h"
#include "portable.h"
#include "projdefs.h"
#include "queue.h"
#include "semphr.h"
#include "stack_macros.h"
#include "task.h"
#include "timers.h"
#include "stream_buffer.h"

#include "arc_freertos_exceptions.h"

/** global macros that may need */
#define os_hal_exc_init()               freertos_exc_init()

#ifndef SYSCALL_PREFIX
#define SYSCALL_PREFIX(x)		x
#endif

extern int main(void);
extern void board_init(void);
extern void board_timer_update(uint32_t precision);
extern void platform_main(void);
extern void board_main(void);

#define BOARD_SYS_TIMER_MS_HZ           (1000)
#define BOARD_CPU_CLOCK              (1000000)

#define BOARD_SYS_TIMER_ID              TIMER_0
#define BOARD_SYS_TIMER_INTNO           INTNO_TIMER0
#define BOARD_OS_TIMER_ID               TIMER_0
#define BOARD_OS_TIMER_INTNO            INTNO_TIMER0
#define BOARD_SYS_TIMER_HZ              (1000)

#endif /* _BOARD_H_ */

/** @} end of group BOARD_COMMON */
