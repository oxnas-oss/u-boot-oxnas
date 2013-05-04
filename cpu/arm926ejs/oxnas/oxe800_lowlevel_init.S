/*
 * Low-level board setup code for OxSemi OXE800 SoC based boards.
 *
 * (C) Copyright 2005
 * Oxford Semiconductor Ltd
 *
 * (C) Copyright 2013
 * Stephan Linz <linz@li-pro.net>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <version.h>

#include <asm/arch/memory-map.h>
#include <asm/arch/sysctrl.h>
#include <asm/arch/ddrctrl.h>

/*
 * Use estimation of processor speed to calculate number of cycles delay.
 *
 * Delay count is nominal (ARMCLK frequency x delay time) / loop count.
 * Expressing 200us as 200/1000000 and re-arranging for the worst case
 * szenario of highest possible ARMCLK gives the expression below.
 */
#if (CONFIG_OXNAS_FPGA == 1)
#define DELAY_200US	((CONFIG_OXNAS_MAIN_CLK  / (5 * 1000000)) * 200)
#else
#define DELAY_200US	(((CONFIG_OXNAS_PLL400_CLK / 2)  / (5 * 1000000)) * 200)
#endif

#ifndef CONFIG_SKIP_LOWLEVEL_INIT

.globl lowlevel_init
lowlevel_init:
	/*
	 * register allocations
	 * r0 - delay counter and scratch
	 * r1 - address register
	 * r2 - data register
	 * r3 - index to table pointer
	 * r4 - iteration counter.
	 * r5 - base address of register bank
	 *
	 * r6 - hold return address.
	 * lr - (R14) link register
	 * pc - (R15) program counter.
	 */

	/*
	 * Check that not in SDRAM execution. Suicide if re-initialise DRAM.
	 * Controller function is linked to execute in SDRAM must be in ROM
	 * or SRAM if not there. Check for wrong place.
	 */
#ifdef CONFIG_OXNAS_INIT_SDRAM
	adrl r0, lowlevel_init		/* Relative location of function start.*/
	ldr  r1, _lowlevel_init
	cmp  r0, r1
	moveq pc, lr
#else
	mov pc, lr
#endif

	/* Establish a working setup for the SDRAM */
	mov r6, lr

	/* Assert reset to the DDR core */
	ldr r0, =SYS_CTRL_RSTEN_SET_CTRL
	ldr r1, =1
	ldr r2, =SYS_CTRL_RSTEN_DDR_BIT
	mov r1, r1, lsl r2
	str r1, [r0]

	/* Deassert reset to the DDR core */
	ldr r0, =SYS_CTRL_RSTEN_CLR_CTRL
	str r1, [r0]

	/* Turn on the DDR core clock */
	ldr r0, =SYS_CTRL_CKEN_SET_CTRL
	ldr r1, =1
	ldr r2, =SYS_CTRL_CKEN_DDR_BIT
	mov r1, r1, lsl r2
	str r1, [r0]

	/* Start using the initialisation value list */
	adrl r3, init_table

	/* Copy next 6 entries from DDR init table*/
	ldr r4, =6
loop0:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop0

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

#if !CONFIG_OXNAS_TEST_BRD
	/* Copy next entry */
	ldr r4, =1
loopx:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loopx

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay
#endif

	/* Copy next entry */
	ldr r4, =1
loop1:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop1

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

	/* Copy next entry */
	ldr r4, =1
loop2:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop2

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

	/* Copy next entry */
	ldr r4, =1
loop3:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop3

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

	/* Copy next 5 entries */
	ldr r4, =5
loop4:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop4

	/* SDRAM initialised so now exit. */
	mov lr, r6
	mov pc, lr

/*
 *  delay()
 *
 *  uses 1 + r0 * 5 cycles
 */
delay:
	nop
	nop
	nop
	subs r0, r0, #1
	bne delay
	mov pc, lr

_lowlevel_init:
	.word lowlevel_init

/* Table of address, data for loading into the DRAM controller */
init_table:

	/*
	 * Configure for a single DDR device
	 */

	.word SYS_CTRL_CKEN_SET_CTRL,	(1 << SYS_CTRL_CKEN_DDR_BIT)
	.word SYS_CTRL_RSTEN_CLR_CTRL,	(1 << SYS_CTRL_RSTEN_DDR_BIT)

	.word DDR_CTRL_CFG,	(1 << 31)				\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)

	/* Enable DDR core and all clients  */
	.word DDR_CTRL_BLKEN,	DDR_CTRL_BLKEN_CLIENTS_MASK		\
				| DDR_CTRL_BLKEN_CORE

	/* Set I/O drive strengths */
	.word DDR_CTRL_IOC,	0x000001e4

	/* DLL to automatic with starting 1 */
	.word DDR_CTRL_DLL,	DDR_CTRL_DLL_OFFSET(1)			\
				| DDR_CTRL_DLL_AUTO			\
				| DDR_CTRL_DLL_NOOFFS			\
				| DDR_CTRL_DLL_ENABLE
	/* 200uS delay */

#if !CONFIG_OXNAS_TEST_BRD
	/* DLL to automatic with offset 3   */
	.word DDR_CTRL_DLL,	DDR_CTRL_DLL_OFFSET(3)			\
				| DDR_CTRL_DLL_AUTO			\
				| DDR_CTRL_DLL_ENABLE
	/* 200uS delay */
#endif

#if (CONFIG_OXNAS_MSIZE == 32)
	.word DDR_CTRL_CFG,	(1 << 31) | (1 << 20)			\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_32MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x030C
#else
	.word DDR_CTRL_CFG,	(1 << 31) | (1 << 20)			\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x030C
#endif

	/* 200uS delay */
	.word DDR_CTRL_CMD,	0x80280400	/* Issue precharge to       */
						/* all banks                */

	/* 200uS delay */
	.word DDR_CTRL_CMD,	0x80210000	/* Enable DLL, disable OCD  */

	/* 200uS delay */
	.word DDR_CTRL_CMD,	0x80200063	/* Set burst length ?,      */
						/* sequential CAS ?         */

	/* Enable all arbiter features */
	.word DDR_CTRL_ARB,	DDR_CTRL_ARB_DATDIR_NCH			\
				| DDR_CTRL_ARB_DATDIR_EN		\
				| DDR_CTRL_ARB_REQAGE_EN		\
				| DDR_CTRL_ARB_LRUBANK_EN		\
				| DDR_CTRL_ARB_MIDBUF

	/* Disable all monitoring */
	.word DDR_CTRL_MON,	0x00000000

	/* Disable and flush all read buffering, due to known h/w bug */
	.word DDR_CTRL_AHB,	DDR_CTRL_AHB_FLUSH_RCACHE_MASK		\
				| DDR_CTRL_AHB_NO_RCACHE_MASK

	/* Do NOT disable HPROT, in example want write coherency */
	.word DDR_CTRL_AHB2,	0x00000000

.ltorg

#endif /* CONFIG_SKIP_LOWLEVEL_INIT */
