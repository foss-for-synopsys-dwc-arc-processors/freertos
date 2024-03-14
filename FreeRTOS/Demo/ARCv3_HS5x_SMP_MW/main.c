/*
 * Copyright (c) 2024 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include "semphr.h"

#include "arc/arc_builtin.h"

/* Priorities at which the tasks are created.  */
#define mainDISPLAY_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
/*-----------------------------------------------------------*/

typedef struct {
	uint64_t 	 taskDelayTicks;
	const char *displayText;
} taskparam_t;

taskparam_t setTaskparam(uint64_t taskDelayMs, const char *displayText) {
	taskparam_t tp = {
		.taskDelayTicks = pdMS_TO_TICKS(taskDelayMs),
		.displayText    = displayText
	};

	return tp;
}

static taskparam_t taskparamA;
static taskparam_t taskparamB;
static taskparam_t taskparamC;
static taskparam_t taskparamD;

static const char *pcTextForTaskA = "TaskA running on Core %u [Times switched: %3u]\r";
static const char *pcTextForTaskB = "TaskB running on Core %u [Times switched: %3u]\r";
static const char *pcTextForTaskC = "TaskC running on Core %u [Times switched: %3u]\r";
static const char *pcTextForTaskD = "TaskD running on Core %u [Times switched: %3u]\r";

static void prvDisplayCoreIdTask( void *pvParameters );
/*-----------------------------------------------------------*/

int main( void )
{
	vTaskSuspendAll();

	vSendString("\r\nARC SMP FreeRTOS Start-Up\r");

	taskparamA = setTaskparam(10, pcTextForTaskA);
	taskparamB = setTaskparam(20, pcTextForTaskB);
	taskparamC = setTaskparam(40, pcTextForTaskC);
	taskparamD = setTaskparam(80, pcTextForTaskD);

	xTaskCreate(
		/* The function that implements the task. */
		prvDisplayCoreIdTask,
		/* Text name for the task, just to help debugging. */
		"TaskA",
		/* The size (in words) of the stack that should be created
		for the task. */
		configMINIMAL_STACK_SIZE,
		/* A parameter that can be passed into the task. */
		(void*) &taskparamA,
		/* The priority to assign to the task.  tskIDLE_PRIORITY
		(which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
		is the highest priority. */
		mainDISPLAY_TASK_PRIORITY,
		/* Used to obtain a handle to the created task.  Not used in
		this simple demo, so set to NULL. */
		NULL
	);

	xTaskCreate(
		/* The function that implements the task. */
		prvDisplayCoreIdTask,
		/* Text name for the task, just to help debugging. */
		"TaskB",
		/* The size (in words) of the stack that should be created
		for the task. */
		configMINIMAL_STACK_SIZE,
		/* A parameter that can be passed into the task. */
		(void*) &taskparamB,
		/* The priority to assign to the task.  tskIDLE_PRIORITY
		(which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
		is the highest priority. */
		mainDISPLAY_TASK_PRIORITY,
		/* Used to obtain a handle to the created task.  Not used in
		this simple demo, so set to NULL. */
		NULL
	);

	xTaskCreate(
		/* The function that implements the task. */
		prvDisplayCoreIdTask,
		/* Text name for the task, just to help debugging. */
		"TaskC",
		/* The size (in words) of the stack that should be created
		for the task. */
		configMINIMAL_STACK_SIZE,
		/* A parameter that can be passed into the task.  Not used
		in this simple demo. */
		(void*) &taskparamC,
		/* The priority to assign to the task.  tskIDLE_PRIORITY
		(which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
		is the highest priority. */
		mainDISPLAY_TASK_PRIORITY,
		/* Used to obtain a handle to the created task. */
		NULL
	);

	xTaskCreate(
		/* The function that implements the task. */
		prvDisplayCoreIdTask,
		/* Text name for the task, just to help debugging. */
		"TaskD",
		/* The size (in words) of the stack that should be created
		for the task. */
		configMINIMAL_STACK_SIZE,
		/* A parameter that can be passed into the task.  Not used
		in this simple demo. */
		(void*) &taskparamD,
		/* The priority to assign to the task.  tskIDLE_PRIORITY
		(which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
		is the highest priority. */
		mainDISPLAY_TASK_PRIORITY,
		/* Used to obtain a handle to the created task. */
		NULL
	);

	xTaskResumeAll();
	vTaskSuspend(NULL);
	/* Should never reach here. */
	for( ; ; );
	return 0;
}
/*-----------------------------------------------------------*/

static void prvDisplayCoreIdTask( void *pvParameters )
{
	TickType_t xNextWakeTime;
	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	uint64_t taskLocalTimesSwitched = 0;
	taskparam_t *pcTaskparam = (taskparam_t*) pvParameters;
	char buf[80];

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  The task will not consume any CPU time while it is in the
		Blocked state. */
		vTaskDelayUntil(&xNextWakeTime, pcTaskparam->taskDelayTicks);

		unsigned int coreId = arconnect_get_core_id();

		taskLocalTimesSwitched++;

		sprintf(buf, pcTaskparam->displayText, coreId, taskLocalTimesSwitched);
		vSendString(buf);
	}
}
/*-----------------------------------------------------------*/