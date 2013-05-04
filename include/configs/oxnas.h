/*
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * If we are developing, we might want to start U-Boot from ram
 * so we MUST NOT initialize critical regs like mem-timing ...
 */
#define CONFIG_INIT_CRITICAL		/* undef for developing             */

/*
 * OXNAS Architecture (OXE800 or OXE810)
 */
#define CONFIG_ARM926EJS	1	/* This is an ARM926EJS CPU         */
#define CONFIG_OXNAS		1	/* on a OxSemi NAS derivate         */
#ifndef	CONFIG_OXNAS_CHIP
#define CONFIG_OXNAS_CHIP	810	/* as OXE810(D)SE                   */
#endif					/* alternat. is 800 for OXE800(D)SE */

#if (CONFIG_OXNAS_CHIP == 810)
#ifndef	CONFIG_OXNAS_FPGA
#define CONFIG_OXNAS_FPGA	0	/* SoC-I/O in ASIC, no external FPGA*/
#endif
#else
#undef CONFIG_OXNAS_FPGA
#define CONFIG_OXNAS_FPGA	0	/* only significant for OXE810      */
#endif

#if (CONFIG_OXNAS_CHIP == 800)
#ifndef	CONFIG_OXNAS_TEST_BRD
#define CONFIG_OXNAS_TEST_BRD	0	/* final, no test board (production)*/
#endif
#else
#undef CONFIG_OXNAS_TEST_BRD
#define CONFIG_OXNAS_TEST_BRD	0	/* only significant for OXE800      */
#endif

#define CONFIG_OXNAS_INIT_SDRAM	1	/* Re-initialise SDRAM controller   */
					/* in platformsetup() when execute  */
					/* in ROM/SRAM.                     */
#if (CONFIG_OXNAS_CHIP == 810)
#ifndef	CONFIG_OXNAS_PROBE_MSIZE
#define	CONFIG_OXNAS_PROBE_MSIZE 1	/* enable probe memory              */
#endif
#else
#undef CONFIG_OXNAS_PROBE_MSIZE
#define	CONFIG_OXNAS_PROBE_MSIZE 0	/* only significant for OXE810      */
#endif

#if !CONFIG_OXNAS_PROBE_MSIZE
#ifndef	CONFIG_OXNAS_MSIZE
#define	CONFIG_OXNAS_MSIZE	64	/* 64 MB, if probing is not enabled */
#endif
#endif

#if (CONFIG_OXNAS_CHIP == 810)
#ifndef	CONFIG_OXNAS_MODT
#define	CONFIG_OXNAS_MODT	150	/* 150 Ohm on-die termination       */
#endif					/* possible values are: 50, 75, 150 */
#else
#undef CONFIG_OXNAS_MODT
#define	CONFIG_OXNAS_MODT	0	/* only significant for OXE810      */
#endif

#ifndef	CONFIG_OXNAS_UART
#define	CONFIG_OXNAS_UART	2	/* use internal UART2 as console    */
#endif					/* possible values are:             */
					/*   0 for use external UART        */
					/*   1 for UART1,    2 for UART2    */
					/*   3 for UART3, >= 4 for UART4    */

/* This must be included AFTER the definition of CONFIG_OXNAS_* */
#include <./configs/oxe8x0.h>

/*
 * High Level Configuration Options
 * (easy to change)
 */
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff      */
					/* for timer/console/ethernet       */

#define CONFIG_CMDLINE_TAG	1	/* enable passing Linux commad line */
#define CONFIG_SETUP_MEMORY_TAGS 1
#define CONFIG_INITRD_TAG	1

#undef CONFIG_MISC_INIT_R		/* not used yet                     */
#undef BOARD_LATE_INIT			/* not used yet                     */

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128 * 1024)	/* regular stack            */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 * 1024)	/* IRQ stack                */
#define CONFIG_STACKSIZE_FIQ	(4 * 1024)	/* FIQ stack                */
#endif

/* 
 * Clock configuration options
 * NOTE: OXNAS use TIMER_CTRL_PRESCALE(TPS_256) --> CFG_OXNAS_RPSCLK / 256 !!!
 */
#define CFG_HZ	((CFG_OXNAS_RPSCLK) / 256)	/* incr. freq: 97.65625 kHz */

/*
 * Miscellaneous configurable options
 */
#define CFG_HUSH_PARSER		1
#define CFG_PROMPT_HUSH_PS2	"> "

#define CFG_LONGHELP			/* undef to save memory             */
#ifdef CFG_HUSH_PARSER
#define CFG_PROMPT		"$ "	/* Monitor Command Prompt           */
#else
#define CFG_PROMPT		"# "	/* Monitor Command Prompt           */
#endif
#define CFG_CBSIZE		256	/* Console I/O Buffer Size          */

/* Print Buffer Size */
#define CFG_PBSIZE	(CFG_CBSIZE+sizeof(CFG_PROMPT)+16)
#define CFG_MAXARGS	16		/* max number of command args       */
#define CFG_BARGSIZE	(CFG_CBSIZE)	/* Boot Argument Buffer Size        */

/* Environment organization */
#define CFG_ENV_SIZE		(8 * 1024)

/* Default location from which bootm etc will load */
#define CFG_LOAD_ADDR		(PHYS_SDRAM_1_PA + 5 * 1024 * 1024)

/* Default location where mtest works on: 12 MB in SDRAM */
#define CFG_MEMTEST_START	(PHYS_SDRAM_1_PA)
#define CFG_MEMTEST_END		(PHYS_SDRAM_1_PA + 12 * 1024 * 1024)

/* Define to NOT include flash support on static bus */
#define CFG_NO_FLASH

/*
 * Size of malloc() pool; this lives below the uppermost 128 KiB which are
 * used for the RAM copy of the uboot code
 */
#define CFG_MALLOC_LEN		(CFG_ENV_SIZE + 128 * 1024)
#define CFG_GBL_DATA_SIZE	128	/* bytes reserved for initial data  */

/* Console configuration */
#define CONFIG_CONS_INDEX	1
#define CONFIG_BAUDRATE		115200
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*
 * Monitor commands
 */
#define CONFIG_COMMANDS		(CFG_CMD_MISC		| \
				 CFG_CMD_BDI		| \
				 CFG_CMD_CONSOLE	| \
				 CFG_CMD_MEMORY		| \
				 CFG_CMD_ENV		| \
				 CFG_CMD_RUN		| \
				 CFG_CMD_IMI)

/* This must be included AFTER the definition of CONFIG_COMMANDS */
#include <cmd_confdefs.h>

/*
 * Environment organization
 */
#define CFG_ENV_IS_NOWHERE
#define CONFIG_ENV_OVERWRITE

/*
 * Low Level Configuration Options
 * (depends on platform configuration)
 */

/* Timer */
#define CFG_TIMERBASE		(RPS_TIMER1)

/* RAM: SRAM and SDRAM */
#define CONFIG_NR_DRAM_BANKS		1	/* We have 1 bank of SDRAM  */
#define CFG_SRAM_BASE			(PHYS_SRAM_PA)
#define CFG_SRAM_SIZE			(PHYS_SRAM_SIZE)

/* Serial Console (UART) */
#define CFG_NS16550			1
#define CFG_NS16550_SERIAL		1
#define CFG_NS16550_REG_SIZE		1

#if !CONFIG_OXNAS_UART

#undef USE_UART_FRACTIONAL_DIVIDER
#define CFG_NS16550_CLK			16000000
#define CFG_NS16550_COM1		0x28000000

#else

#define CFG_NS16550_CLK			(CONFIG_OXNAS_SYSCLK)

#if (CONFIG_OXNAS_UART == 1)

#define CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CFG_NS16550_COM1		(UART_1_BASE_PA)

#elif (CONFIG_OXNAS_UART == 2)

#undef CONFIG_OXNAS_UART1
#define CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CFG_NS16550_COM1		(UART_2_BASE_PA)

#elif (CONFIG_OXNAS_UART == 3)

#undef CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#define CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CFG_NS16550_COM1		(UART_3_BASE_PA)

#else

#undef CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#define CONFIG_OXNAS_UART4
#define CFG_NS16550_COM1		(UART_4_BASE_PA)

#endif

#endif

#endif /* __CONFIG_H */
