/*
    FreeRTOS V9.0.1 - Copyright (C) 2017 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


/*
	BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER FOR UART0.

	This file contains all the serial port components that must be compiled
	to ARM mode.  The components that can be compiled to either ARM or THUMB
	mode are contained in serial.c.

*/

/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* Demo application includes. */
#include "serial.h"
#include "board/board.h"
#include "device/device_hal/inc/dev_uart.h"

/*-----------------------------------------------------------*/

/* Constant to access the VIC. */
#define serCLEAR_VIC_INTERRUPT			( ( unsigned long ) 0 )

/* Constants to determine the ISR source. */
#define serSOURCE_THRE				( ( unsigned char ) 0x02 )
#define serSOURCE_RX_TIMEOUT			( ( unsigned char ) 0x0c )
#define serSOURCE_ERROR				( ( unsigned char ) 0x06 )
#define serSOURCE_RX				( ( unsigned char ) 0x04 )
#define serINTERRUPT_SOURCE_MASK		( ( unsigned char ) 0x0f )

/* Queues used to hold received characters, and characters waiting to be
transmitted. */
static QueueHandle_t xRxedChars;
static QueueHandle_t xCharsForTx;
static volatile long lTHREEmpty;

/*-----------------------------------------------------------*/

/*
 * The queues are created in serialISR.c as they are used from the ISR.
 * Obtain references to the queues and THRE Empty flag.
 */
void vSerialISRCreateQueues( unsigned portBASE_TYPE uxQueueLength, QueueHandle_t *pxRxedChars, QueueHandle_t *pxCharsForTx, long volatile **pplTHREEmptyFlag );

/*-----------------------------------------------------------*/
void vSerialISRCreateQueues(	unsigned portBASE_TYPE uxQueueLength, QueueHandle_t *pxRxedChars,
								QueueHandle_t *pxCharsForTx, long volatile **pplTHREEmptyFlag )
{
	/* Create the queues used to hold Rx and Tx characters. */
	xRxedChars = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xCharsForTx = xQueueCreate( uxQueueLength + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );

	/* Pass back a reference to the queues so the serial API file can
	post/receive characters. */
	*pxRxedChars = xRxedChars;
	*pxCharsForTx = xCharsForTx;

	/* Initialise the THRE empty flag - and pass back a reference. */
	lTHREEmpty = ( long ) pdTRUE;
	*pplTHREEmptyFlag = &lTHREEmpty;
}

void vSerial_RXCallback (void *par)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	DEV_UART *uart_obj = (DEV_UART *)par;
	uint32_t bytes_avail = 0;
	uint8_t cChar;

	if (uart_obj == NULL) { return; }

	uart_obj->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&bytes_avail));
	while (bytes_avail > 0) {
		uart_obj->uart_read((void *)(&cChar), 1);
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
		bytes_avail --;
	}
	if ( xHigherPriorityTaskWoken )	{
		portYIELD_FROM_ISR();
	}
}

void vSerial_TXCallback (void *par)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	DEV_UART *uart_obj = (DEV_UART *)par;
	uint32_t bytes_avail = 0;
	uint8_t cChar;

	if (uart_obj == NULL) { return; }

	uart_obj->uart_control(UART_CMD_GET_TXAVAIL, (void *)(&bytes_avail));
	while (bytes_avail > 0) {
		if ( xQueueReceiveFromISR( xCharsForTx, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE ) {
			uart_obj->uart_write((const void *)(&cChar), 1);
			bytes_avail --;
		} else {
			/* There are no further characters
			queued to send so we can indicate
			that the THRE is available. */
			lTHREEmpty = pdTRUE;
			uart_obj->uart_control(UART_CMD_SET_TXINT, (void *)(0));
			break;
		}
	}
	if ( xHigherPriorityTaskWoken )	{
		portYIELD_FROM_ISR();
	}
}