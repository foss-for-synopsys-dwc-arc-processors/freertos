/*
 * Copyright (c) 2022 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdio.h>
#include "ns16550-virt.h"
#include "portmacro.h"
/*-----------------------------------------------------------
* Application specific definitions.
*
* These definitions should be adjusted for your particular hardware and
* application requirements.
*
* THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
* FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
*
* See http://www.freertos.org/a00110.html.
*----------------------------------------------------------*/

#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     1
#define configCPU_CLOCK_HZ                      (( unsigned long ) 1000000)
#define configTICK_RATE_HZ                      (( TickType_t ) 1000)
#define configMAX_PRIORITIES                    (4)
#define configMINIMAL_STACK_SIZE                (( unsigned short ) 128)
#define configTOTAL_HEAP_SIZE                   (( size_t ) (64 * 1024))
#define configMAX_TASK_NAME_LEN                 (10)
#define configUSE_TRACE_FACILITY                0
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_MUTEXES                       1

/* Software timer related definitions. */
#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH 5
#define configTIMER_TASK_STACK_DEPTH ( configMINIMAL_STACK_SIZE * 2 )

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         (2)

/* Set the following definitions to 1 to include the API function, or zero
   to exclude the API function. */

#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           0
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xQueueGetMutexHolder            1

#endif /* FREERTOS_CONFIG_H */
