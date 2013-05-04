/*
 * Board specific setup info
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

#if (CONFIG_OXNAS_CHIP == 810)

/*
 * Use estimation of processor speed to calculate number of cycles delay.
 *
 * Delay count is nominal (PLL200 frequency x delay time) / loop count.
 * Expressing 200us as 200/1000000 and re-arranging gives the expression
 * below.
 */

#define DELAY_200US	((CONFIG_OXNAS_ARMCLK  / (5 * 1000000)) * 200)
#define DELAY_300US	((CONFIG_OXNAS_ARMCLK  / (5 * 1000000)) * 300)

/* this is 8 cycles of ? so choose 8 resulting in 40 cycles */
#define DELAY_1S	((DELAY_200US) * 5000)
#define DELAY_8		8
#define DELAY_200	200


.globl platformsetup
platformsetup:
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
	adrl r0, platformsetup      /* Relative location of function start.*/
	ldr  r1, _platformsetup
	cmp  r0, r1
	moveq pc, lr
#else
	mov pc, lr
#endif

	/* Establish a working setup for the SDRAM */
	mov r6, lr

#if (CONFIG_OXNAS_FPGA == 1)

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

	/* Copy first 6 entries */
	ldr r4, =6
loop0:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop0

	/* Delay for 200uS while DRAM controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

	/* Copy next 4 entries */
	ldr r4, =4
loop1:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop1

	/* Wait at least 200 clock cycles. */
	ldr r0, =DELAY_200
	bl delay

	/* Copy next 2 entries */
	ldr r4, =2
loop2:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop2

	/* Wait at least 8 clock  cycles. */
	ldr r0, =DELAY_8
	bl delay

	/* Copy next 9 entries */
	ldr r4, =9
loop3:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop3

	/* SDRAM initialised so now exit. */
	mov lr, r6
	mov pc, lr

#else /* ASIC with DDR2 */

	/*
	 * Change clock speed on chip to get overclock.
	 */

	/* Turn on the DDR core and phy clocks */
	ldr r0, =SYS_CTRL_CKEN_SET_CTRL
	ldr r1, =1
	ldr r2, =SYS_CTRL_CKEN_DDR_BIT
	mov r1, r1, lsl r2
	str r1, [r0]
	ldr r1, =1
	ldr r2, =SYS_CTRL_CKEN_DDR_PHY_BIT
	mov r1, r1, lsl r2
	str r1, [r0]

	/* Assert reset to the DDR core and phy */
	ldr r0, =SYS_CTRL_RSTEN_SET_CTRL
	ldr r1, =1
	ldr r2, =SYS_CTRL_RSTEN_DDR_PHY_BIT
	mov r1, r1, lsl r2
	str r1, [r0]
	ldr r1, =1
	ldr r2, =SYS_CTRL_RSTEN_DDR_BIT
	mov r1, r1, lsl r2
	str r1, [r0]

	/* Deassert reset to the DDR core and phy*/
	ldr r0, =SYS_CTRL_RSTEN_CLR_CTRL
	ldr r1, =1
	ldr r2, =SYS_CTRL_RSTEN_DDR_PHY_BIT
	mov r1, r1, lsl r2
	str r1, [r0]
	ldr r1, =1
	ldr r2, =SYS_CTRL_RSTEN_DDR_BIT
	mov r1, r1, lsl r2
	str r1, [r0]

	/* Start using the initialisation value list */
	adrl r3, init_table

	/*
	 * Copy first 14 entries of DDR core setup (section A).
	 */
	ldr r4, =14
loop0:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne loop0

	/* Delay for 200uS while DDR controller stabilises. */
	ldr r0, =DELAY_200US
	bl delay

	/*
	 * Copy next 13 entries of DDR device commands (section B).
	 */
	ldr r4, =13
loop1:
	ldmia r3!, {r1, r2}
	str r2, [r1]

	/* Wait at least 200 clock cycles between ram chip command writes */
	ldr r0, =DELAY_200
	bl delay

	subs r4, r4, #1
	bne loop1

	/*
	 * Copy final DDR controller setup to set memory size/banks
	 * (section C).
	 */
	ldmia r3!, {r1, r2}
	str r2, [r1]

#if CONFIG_OXNAS_PROBE_MSIZE
	/* Load the probe values into SDRAM */
	adrl r3, probe_table
	mov r4, #4
pl1:
	ldmia r3!, {r1, r2}
	str r2, [r1]
	subs r4, r4, #1
	bne pl1

	/* Get the current contents of the DDR controller config register */
	adrl r1, ddr_ctr_cfg_reg_addr
	ldr r1, [r1]
	ldr r1, [r1]

	/* Zero the number of banks field - bit 23*/
	mov r2, #1
	bic r1, r1, r2, lsl #DDR_CTRL_CFG_BANKS_BIT

	/* Zero the size field - bits 17-20 inclusive */
	mov r2, #(DDR_CTRL_CFG_SIZE_MASK >> DDR_CTRL_CFG_SIZE_BIT)
	bic r1, r1, r2, lsl #DDR_CTRL_CFG_SIZE_BIT

	/* First probe location tells us the SDRAM size */
	adrl r3, probe_table
	ldr r0, [r3]
	ldr r0, [r0]

	/* Is size 64MB? */
	ldr r2, [r3, #28]	/* Get probe value 4 */
	cmp r0, r2
	moveq r4, #PO2_64MB
	orreq r1, r1, r4, lsl #DDR_CTRL_CFG_SIZE_BIT
	beq pl2

	/* Is 128M or 256M so set banks to 8 */
	mov r4, #1
	orr r1, r1, r4, lsl #DDR_CTRL_CFG_BANKS_BIT

	/* Is size 128MB? */
	ldr r2, [r3, #20]	/* Get probe value 3 */
	cmp r0, r2
/* bug:	moveq r4, #PO2_128MB	   DDR controller does not work at 128M, */
	moveq r4, #PO2_256MB	/* fix: ... use 256M instead */
	orreq r1, r1, r4, lsl #DDR_CTRL_CFG_SIZE_BIT
	beq pl2

	/* Must be 256MB, or something is very wrong */
	mov r4, #PO2_256MB
	orr r1, r1, r4, lsl #DDR_CTRL_CFG_SIZE_BIT

pl2:
	/* Write the revised contents to the DDR controller config register */
	adrl r2, ddr_ctr_cfg_reg_addr
	ldr r2, [r2]
	str r1, [r2]
#endif

	/* SDRAM setup complete */
	mov lr, r6
	mov pc, lr
#endif /* FPGA with DDR / ASIC with DDR2 */

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

_platformsetup:
	.word platformsetup


/* Table of address, data for loading into the DRAM controller */
init_table:

#if CONFIG_OXNAS_FPGA

	/*
	 * Configure for a single DDR device on FPGA
	 */

	/* Enable the DDR in SDR mode and width 32 bits (default 64 MB) */
	.word DDR_CTRL_CFG,	DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)	\
				| DDR_CTRL_CFG_SDR

	.word DDR_CTRL_TIMING0,	0x04442032	/* SDR mode timings - #0    */
	.word DDR_CTRL_TIMING1,	0x570A0907	/* SDR mode timings - #1    */
	.word DDR_CTRL_TIMING2,	0x00000002	/* SDR mode timings - #2    */

	/* Enable DDR core, but not clients yet */
	.word DDR_CTRL_BLKEN,	DDR_CTRL_BLKEN_CORE

	/* Enable CK and set DLL mode to manual with starting 1 */
	.word DDR_CTRL_DLL,	DDR_CTRL_DLL_OFFSET(1)		\
				| DDR_CTRL_DLL_ENABLE
	/* 200uS delay */

	.word DDR_CTRL_CMD,	0x80200000	/* Assert CKE for all       */
						/* further commands         */
	.word DDR_CTRL_CMD,	0x80280400	/* Issue precharge to       */
						/* all banks                */
	.word DDR_CTRL_CMD,	0x80200000	/* NOP, as only DDR has     */
						/* real command here        */
	.word DDR_CTRL_CMD,	0x80200022	/* Set burst length 4,      */
						/* sequential CAS 2         */
	/* 200uS delay */

	.word DDR_CTRL_CMD,	0x80280400	/* Issue precharge to       */
						/* all banks                */
	.word DDR_CTRL_CMD,	0x80240000	/* Issue auto-refresh       */
						/* command, CKE not asserted*/
	/* 200uS delay */

	.word DDR_CTRL_CMD,	0x80240000	/* Issue auto-refresh       */
						/* command, CKE not asserted*/
	.word DDR_CTRL_CMD,	0x80200000	/* Assert CKE for all       */
						/* further commands         */
	.word DDR_CTRL_CMD,	0x80200022	/* Set burst length 4,      */
						/* sequential CAS 2         */

	.word DDR_CTRL_CFG,	DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x0186	/* SDR, size and width and  */
				/* refresh rate, assuming 25Mhz clk to SDR, */
				/* divide down to get 15.625uS refresh rate */

	/* Set I/O drive strengths */
	.word DDR_CTRL_IOC,	0x00000124

	/* Enable all arbiter features */
	.word DDR_CTRL_ARB,	DDR_CTRL_ARB_DATDIR_NCH			\
				| DDR_CTRL_ARB_DATDIR_EN		\
				| DDR_CTRL_ARB_REQAGE_EN		\
				| DDR_CTRL_ARB_LRUBANK_EN		\
				| DDR_CTRL_ARB_MIDBUF

	/* Disable all monitoring */
	.word DDR_CTRL_MON,	0x00000000

	/* Disable and flush all read buffering */
	.word DDR_CTRL_AHB,	DDR_CTRL_AHB_FLUSH_RCACHE_MASK		\
				| DDR_CTRL_AHB_NO_RCACHE_MASK

	/* Enable all client interfaces */
	.word DDR_CTRL_BLKEN,	DDR_CTRL_BLKEN_CLIENTS_MASK		\
				| DDR_CTRL_BLKEN_CORE

#else	/* ASIC with DDR2 */

	/*
	 * Configure section A - DDR2 controller core configuration.
	 */

	// SECTION A - DDR controller core configuration
	/* Enable the DDR in DDR2 mode and width 16 bits (default 64 MB) */
	.word DDR_CTRL_CFG,	(1 << 31)				\
				| (2 << 20)	/* 4 banks */		\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x0591	/* SDR, size and width and  */
				/* refresh rate, assuming 183.33Mhz clk to  */
				/* SDR, divide down to get 7.8uS refresh    */

	.word DDR_CTRL_TIMING0,	0x04442032	/* ddr-2 mode timings       */
	.word DDR_CTRL_TIMING1,	0x870f0b25	/* ddr-2 mode timings       */
	.word DDR_CTRL_TIMING2,	0x00000a23	/* ddr-2 mode timings       */

	.word DDR_CTRL_PHY3,	0x00072000	/* phy-3 settings           */
	.word DDR_CTRL_PHY2,	0x00022828	/* phy-2 settings, start    */
	.word DDR_CTRL_PHY2,	0x00032828	/* phy-2 settings, on       */

	/* Enable all arbiter features */
	.word DDR_CTRL_ARB,	DDR_CTRL_ARB_DATDIR_NCH			\
				| DDR_CTRL_ARB_DATDIR_EN		\
				| DDR_CTRL_ARB_REQAGE_EN		\
				| DDR_CTRL_ARB_LRUBANK_EN		\
				| DDR_CTRL_ARB_MIDBUF

	/* Disable all monitoring */
	.word DDR_CTRL_MON,	0x00000000

	/* Disable all read buffering */
	.word DDR_CTRL_AHB,	DDR_CTRL_AHB_NO_RCACHE_MASK

	/* no burst accl, no HPROT on ARM Data, but HPROT on ARM Instr. */
	.word DDR_CTRL_AHB2,	(DDR_CTRL_AHB2_IGNORE_HPROT_MASK	\
				 & ~DDR_CTRL_AHB2_IGNORE_HPROT_ARMI)	\
				| DDR_CTRL_AHB2_IGNORE_WRAP_MASK

	/* Enable burst and read cache -- so disable nothing in AHB3 */
	.word DDR_CTRL_AHB3,	0x00000000

	/* Enable write behind prot, but disable all timeouts */
	.word DDR_CTRL_AHB4,	DDR_CTRL_AHB4_EN_WRBEHIND_MASK

	/* Enable DDR core and all clients  */
	.word DDR_CTRL_BLKEN,	DDR_CTRL_BLKEN_CLIENTS_MASK		\
				| DDR_CTRL_BLKEN_CORE
	/* 200uS delay after configuring DDR2 controller core */

	/*
	 * Configure section B - Memory device configuration.
	 */

	.word DDR_CTRL_CMD,	0x807c0000	/* exit something or other  */
	.word DDR_CTRL_CMD,	0x803c0000	/* nop - wake up            */
	.word DDR_CTRL_CMD,	0x80280400	/* precharge all            */
	.word DDR_CTRL_CMD,	0x80220000	/* emr2                     */
	.word DDR_CTRL_CMD,	0x80230000	/* emr3                     */

#if (CONFIG_OXNAS_MODT == 150)			/* Enable DLL and set ODT   */
	.word DDR_CTRL_CMD,	0x80210042	/* ... to 150 Ohm           */
#elif (CONFIG_OXNAS_MODT == 75)
	.word DDR_CTRL_CMD,	0x80210006	/* ... to  75 Ohm           */
#elif (CONFIG_OXNAS_MODT == 50)
	.word DDR_CTRL_CMD,	0x80210046	/* ... to  50 Ohm           */
#else
#error Unsupported memory on-die termination, set CONFIG_OXNAS_MODT \
	to 50, 75, or 150
#endif

	.word DDR_CTRL_CMD,	0x80200733	/* set WR CL BL / reset dll */
	.word DDR_CTRL_CMD,	0x80280400	/* precharge all            */
	.word DDR_CTRL_CMD,	0x80240000	/* auto refresh             */
	.word DDR_CTRL_CMD,	0x80240000	/* auto refresh             */
	.word DDR_CTRL_CMD,	0x80200733	/* set WR CL BL / reset dll */

#if (CONFIG_OXNAS_MODT == 150)
	.word DDR_CTRL_CMD,	0x802103c2	/* ODT 150 Ohm: enable OCD  */
	.word DDR_CTRL_CMD,	0x80210042	/* ... and disable OCD      */
#elif (CONFIG_OXNAS_MODT == 75)
	.word DDR_CTRL_CMD,	0x80210386	/* ODT  75 Ohm: enable OCD  */
	.word DDR_CTRL_CMD,	0x80210006	/* ... and disable OCD      */
#elif (CONFIG_OXNAS_MODT == 50)
	.word DDR_CTRL_CMD,	0x802103c6	/* ODT  50 Ohm: enable OCD  */
	.word DDR_CTRL_CMD,	0x80210046	/* ... and disable OCD      */
#else
#error Unsupported memory on-die termination, set CONFIG_OXNAS_MODT \
	to 50, 75, or 150
#endif

	/*
	 * Configure section C - Final memory size/bank configuration.
	 */

#if CONFIG_OXNAS_PROBE_MSIZE || (CONFIG_OXNAS_MSIZE == 256)
	.word DDR_CTRL_CFG,	(1 << 31)				\
				| (0xa << 20)	/* 8 banks */		\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_256MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x0591	/* 1425 clocks for 7.8us    */
#elif (CONFIG_OXNAS_MSIZE == 128)
	.word DDR_CTRL_CFG,	(1 << 31)				\
				| (0xa << 20)	/* 8 banks */		\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_128MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x0591	/* 1425 clocks for 7.8us    */
#elif (CONFIG_OXNAS_MSIZE == 64)
	.word DDR_CTRL_CFG,	(1 << 31)				\
				| (2 << 20)	/* 4 banks */		\
				| DDR_CTRL_CFG_SIZE_MBPO2(PO2_64MB)	\
				| DDR_CTRL_CFG_SDR			\
				| 0x0591	/* 1425 clocks for 7.8us    */
#else
#error Unsupported memory size, set CONFIG_OXNAS_PROBE_MSIZE \
	or CONFIG_OXNAS_MSIZE to 64, 128 or 256
#endif

#endif /* FPGA with DDR / ASIC with DDR2 */

#if CONFIG_OXNAS_PROBE_MSIZE
ddr_ctr_cfg_reg_addr:
	.word DDR_CTRL_CFG

probe_table:
	.word PHYS_SDRAM_1_PA,			0x12345678
	.word PHYS_SDRAM_1_PA + 0x40,		0xdeadbeef
	.word PHYS_SDRAM_1_PA + SZ_128M,	0xfafafafa
	.word PHYS_SDRAM_1_PA + SZ_128M + 0x40,	0xabcdef01
#endif

.ltorg

#endif /* (CONFIG_OXNAS_CHIP == 810) */
