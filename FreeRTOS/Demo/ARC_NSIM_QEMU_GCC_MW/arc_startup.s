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
	mov	r0, 0

/* interrupt related init */
	sr	r0, [AUX_IRQ_ACT]
	sr	r0, [AUX_IRQ_CTRL]
	sr	r0, [AUX_IRQ_HINT]

/* use the new vector table to replace the old one */
	sr	exc_entry_table, [AUX_INT_VECT_BASE]
#ifdef __GNU__
	mov	gp, __SDATA_BEGIN__	/* init small-data base register */
#else
	mov	gp, _f_sdata	/* init small-data base register */
#endif
	mov	fp, 0		/* init fp register */
	mov	sp, _e_stack	/* init stack pointer */

_arc_reset_stage3:
_s3_copy_data:
	mov	r0, _f_data
	mov	r1, _load_addr_data
	cmp	r0, r1
	jeq	_s3_clear_bss

	mov	r3, _e_data
_s3_copy_data_loop:
	ld.ab	r2, [r1, 4]
	st.ab	r2, [r0, 4]
	cmp	r0, r3
	jlt	_s3_copy_data_loop
_s3_clear_bss:
	mov	r0, _f_bss
	mov	r1, _e_bss
	cmp	r0, r1
	jge	_arc_reset_call_main
	mov	r2, 0
_s3_clear_bss_loop:
	st.ab	r2, [r0, 4]
	cmp	r0, r1
	jlt	_s3_clear_bss_loop

/* STAGE 3: go to main */

_arc_reset_call_main:

/* board level library init */
	jl	board_main	/* board-level main */

/** @endcond */

/** }@*/
