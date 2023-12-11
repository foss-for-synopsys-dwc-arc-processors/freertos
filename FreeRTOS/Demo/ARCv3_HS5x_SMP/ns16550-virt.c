/*
 * Copyright (c) 2022 Synopsys
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
	size_t i;
	uintptr_t addr = NS16550_ADDR;

	portENTER_CRITICAL();

	for (i = 0; i < strlen(s); i++) {
		vOutNS16550( addr, s[i] );
	}
	vOutNS16550( addr, '\n' );

	portEXIT_CRITICAL();
}
