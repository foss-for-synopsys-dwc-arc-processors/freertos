/*
 * Copyright (c) 2022 Synopsys
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * \file
 * \ingroup ARC_HAL_MISC
 * \brief header file for arc feature configuration
 */

/**
 * \addtogroup ARC_HAL_MISC
 * @{
 */

#ifndef _ARC_FEATURE_CONFIG_H_
#define _ARC_FEATURE_CONFIG_H_

/**
 * DO NOT MODIFY THIS PART
 *
 * The information of memory devices on the board
 */
#ifdef ARC_FEATURE_ICCM_PRESENT
#ifndef ICCM_SIZE
#define ICCM_SIZE       ARC_FEATURE_ICCM_SIZE
#endif
#ifndef ICCM_START
#define ICCM_START      ARC_FEATURE_ICCM_BASE
#endif
#else
#ifndef ICCM_SIZE
#define ICCM_SIZE       0x80000000
#endif
#ifndef ICCM_START
#define ICCM_START      0x0
#endif
#endif

#ifdef ARC_FEATURE_DCCM_PRESENT
#ifndef DCCM_SIZE
#define DCCM_SIZE       ARC_FEATURE_DCCM_SIZE
#endif
#ifndef DCCM_START
#define DCCM_START      ARC_FEATURE_DCCM_BASE
#endif
#else
#ifndef DCCM_SIZE
#define DCCM_SIZE       0x80000000
#endif
#ifndef DCCM_START
#define DCCM_START      0x80000000
#endif
#endif

/**
 * The default regions assigned for application to use,
   by default, each region will use all the space
   of each memory device
 * User can config the start address and the size of
   the regions to limit the application using
 */
#ifndef REGION_ICCM_START
#define REGION_ICCM_START       ICCM_START
#define REGION_ICCM_SIZE        ICCM_SIZE
#endif

#ifndef REGION_DCCM_START
#define REGION_DCCM_START       DCCM_START
#define REGION_DCCM_SIZE        DCCM_SIZE
#endif

/**
 * The default regions used to generate link script
 * User can select region by configuring REGION_ROM and REGION_RAM
 * For REGION_ROM, REGION_ICCM are available
 * For REGION_RAM, REGION_DCCM are available
 */
#ifndef REGION_ROM
#define REGION_ROM      REGION_ICCM
#endif

#ifndef REGION_RAM
#define REGION_RAM      REGION_DCCM
#endif

/** ARC baseline instruction set version number */
#define ARC_FEATURE_ARC_EM          0x4
#define ARC_FEATURE_ARC_HS          0x5

#define ARC_FEATURE_ARC_FAMILY      4

/** ARC PC size */
#define ARC_FEATURE_PC_SIZE             32

/** ARC LPC size */
#define ARC_FEATURE_LPC_SIZE            32

/** ARC Addr size */
#define ARC_FEATURE_ADDR_SIZE           32

/** ARC Endian/Byte Order */
#define ARC_FEATURE_LITTLE_ENDIAN       1234

#define ARC_FEATURE_BYTE_ORDER          ARC_FEATURE_LITTLE_ENDIAN

/** Code density option, if enabled, ARC_FEATURE_CODE_DENSITY will be defined */
#define ARC_FEATURE_CODE_DENSITY        0

/** The number of register file banks */
#define ARC_FEATURE_RGF_NUM_BANKS       2

/** The number of registers replicated per register bank */
#define ARC_FEATURE_RGF_BANKED_REGS     32

/** Interrupt unit presence */
#define ARC_FEATURE_INTERRUPTS_PRESENT  1

/** FIRQ_OPTION configuration option, 1 for enabled, 0 for disabled */
#define ARC_FEATURE_FIRQ                1

/** The number of interrupts */
#define NUM_EXC_INT                     20

/** The number of external interrupts */
#define NUM_EXC_EXT_INT                 16

/** The interrupt priority levels */
#define INT_PRI_MIN                     (-4)

// ARC TIMER_BUILD
/** Timer0 present or not */
#define ARC_FEATURE_TIMER0_PRESENT      1
#define ARC_FEATURE_TIMER0_LEVEL        (1 - 4)
#define ARC_FEATURE_TIMER0_VECTOR       16

/** Timer1 present or not */
#define ARC_FEATURE_TIMER1_PRESENT      1
#define ARC_FEATURE_TIMER1_LEVEL        (0 - 4)
#define ARC_FEATURE_TIMER1_VECTOR       17

// Memory related definitions
/** ICCM Presence, base address and size */
#define ARC_FEATURE_ICCM_PRESENT        1
#define ARC_FEATURE_ICCM_BASE           0x00000000
#define ARC_FEATURE_ICCM_SIZE           0x80000


/** ICCM0 Presence, base address and size */
#define ARC_FEATURE_ICCM0_PRESENT       1
#define ARC_FEATURE_ICCM0_BASE          0x00000000
#define ARC_FEATURE_ICCM0_SIZE          0x40000

/** DCCM Presence, base address and size */
#define ARC_FEATURE_DCCM_PRESENT        1
#define ARC_FEATURE_DCCM_BASE           0x80000000
#define ARC_FEATURE_DCCM_SIZE           0x80000
#define ARC_FEATURE_DCCM_INTERLEAVE    1

/** Peripheral memory region(DMP) base address, if dmp configured, this macro will be defined as base address */
#define ARC_FEATURE_DMP_PERIPHERAL      0xf0000000

/** Option to use the default exception entry table */
#define ARC_FEATURE_USE_DEFAULT_EXC_ENTRY_TABLE         1

/** Option to use the default exception interrupt handler table */
#define ARC_FEATURE_USE_DEFAULT_EXC_INT_HANDLER_TABLE   1

#endif  /* _ARC_FEATURE_CONFIG_H_ */

/** @} */
