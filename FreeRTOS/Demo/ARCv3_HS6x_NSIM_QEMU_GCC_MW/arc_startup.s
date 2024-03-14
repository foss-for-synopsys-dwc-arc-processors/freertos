/*
 * Copyright (c) 2022 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @ingroup ARC_HAL_STARTUP
 * @brief assembly part of startup process
 */

/**
 * @addtogroup ARC_HAL_STARTUP
 * @{
 */
/** @cond STARTUP_ASM */

#define __ASSEMBLY__
#include "arc/arc.h"
#include "arc/arc_asm_common.h"

	.file "arc_startup.s"


.extern	board_main
.extern exc_entry_table

/* initial vector table */
	.section .init_vector, "a"
	.long _arc_reset
	.section .init_bootstrap, "ax"
	.global _arc_reset
	.global _start
	.align 4
_start:
_arc_reset:
_arc_reset_stage1:
	kflag  STATUS32_RESET_VALUE

/* STAGE 1 */

/* necessary hardware should be done first to speed up initialization
	1. system clk
	2. mem controller must be initialized before any access to external
	mem.
	3. others
*/

/* STAGE 2: init necessary registers */

_arc_reset_stage2:
	movl	r0, 0

/* interrupt related init */
	srl	r0, [AUX_IRQ_ACT]
	srl	r0, [AUX_IRQ_CTRL]
	srl	r0, [AUX_IRQ_HINT]

/* use the new vector table to replace the old one */
	movl r0, exc_entry_table
	srl  r0, [AUX_INT_VECT_BASE]
	movl r0, 0
#ifdef __GNU__
	movl	gp, __SDATA_BEGIN__	/* init small-data base register */
#else
	movl	gp, _f_sdata	/* init small-data base register */
#endif
	movl	fp, 0		/* init fp register */
	movl	sp, _e_stack	/* init stack pointer */

_arc_reset_stage3:
_s3_copy_data:
	movl	r0, _f_data
	movl	r1, _load_addr_data
	cmpl	r0, r1
	jeq	_s3_clear_bss

	movl	r3, _e_data
_s3_copy_data_loop:
	ldl.ab	r2, [r1, 8]
	stl.ab	r2, [r0, 8]
	cmpl	r0, r3
	jlt	_s3_copy_data_loop
_s3_clear_bss:
	movl	r0, _f_bss
	movl	r1, _e_bss
	cmpl	r0, r1
	jge	_arc_reset_call_main
	movl	r2, 0
_s3_clear_bss_loop:
	stl.ab	r2, [r0, 8]
	cmpl	r0, r1
	jlt	_s3_clear_bss_loop

/* STAGE 3: go to main */

_arc_reset_call_main:

/* board level library init */
	jl	board_main	/* board-level main */

/** @endcond */

/** }@*/