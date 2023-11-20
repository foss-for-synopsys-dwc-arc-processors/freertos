/*
 * Copyright (c) 2022 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <FreeRTOS.h>
#include <string.h>

#ifndef NS16550_VIRT_H_
#define NS16550_VIRT_H_

#define NS16550_ADDR		0xf0000000UL

void vSendString( const char * s );

#endif /* NS16550_VIRT_H_ */
