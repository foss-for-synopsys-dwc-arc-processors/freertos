/*
 * Copyright (c) 2024 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ns16550-virt.h"

/* register definitions */
#define REG_THR		0x00 /* Transmitter holding reg. */

static void writeb( uint8_t b, uintptr_t addr )
{
	*( ( volatile uint8_t *) addr ) = b;
}

static void vOutNS16550( uintptr_t address, unsigned char c )
{
	uintptr_t addr = address;

	writeb( c, addr + REG_THR );
}

void vSendString( const char *s )
{
	UBaseType_t uxSavedInterruptStatus = portENTER_CRITICAL_FROM_ISR();
	vPortGetSpinLock(configSEND_STRING_LOCK_ID);

	size_t i;
	uintptr_t addr = NS16550_ADDR;

	for (i = 0; i < strlen(s); i++) {
		vOutNS16550( addr, s[i] );
	}
	vOutNS16550( addr, '\n' );

	vPortReleaseSpinLock(configSEND_STRING_LOCK_ID);
	portEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
}