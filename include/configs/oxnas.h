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

#include <asm/arch/memory-map.h>

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

/* OXNAS SoC static main clock */
#ifndef CONFIG_OXNAS_MAIN_CLK
#define CONFIG_OXNAS_MAIN_CLK	25000000	/* from 25.00 MHz crystal   */
#endif

/* OXNAS SoC static high speed clock */
#ifndef	CONFIG_OXNAS_PLL400_CLK
#define CONFIG_OXNAS_PLL400_CLK	733333333	/* from hard wired ASIC PLL */
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

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARCH_CPU_INIT	1	/* call arch_cpu_init()             */
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff      */
					/* for timer/console/ethernet       */

#define CONFIG_DISPLAY_CPUINFO	1	/* display cpu info                 */
#define CONFIG_DISPLAY_BOARDINFO 1	/* display board info               */
#define CONFIG_SYS_64BIT_VSPRINTF 1	/* needed for cpu info              */

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
 * NOTE: OXNAS use TIMER_CTRL_PRESCALE(TPS_256)
 */
#define CONFIG_SYS_HZ ((CONFIG_OXNAS_MAIN_CLK) / 256)	/* to 97.65625 kHz  */

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_HUSH_PARSER	1
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "

#define CONFIG_SYS_LONGHELP		/* undef to save memory             */
#ifdef CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT	"$ "	/* Monitor Command Prompt           */
#else
#define CONFIG_SYS_PROMPT	"# "	/* Monitor Command Prompt           */
#endif
#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size          */

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16	/* max number of command args       */
#define CONFIG_SYS_BARGSIZE	(CONFIG_SYS_CBSIZE)	/* Boot Arg.Buf.Size*/

/* Environment organization */
#define CONFIG_ENV_SIZE		(8 * 1024)

/* Default location from which bootm etc will load */
#define CONFIG_SYS_LOAD_ADDR		(PHYS_SDRAM_1_PA + 5 * 1024 * 1024)

/* Default location where mtest works on: 12 MB in SDRAM */
#define CONFIG_SYS_MEMTEST_START	(PHYS_SDRAM_1_PA)
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1_PA + 12 * 1024 * 1024)

/* Define to NOT include flash support on static bus */
#define CONFIG_SYS_NO_FLASH

/*
 * Size of malloc() pool; this lives below the uppermost 128 KiB which are
 * used for the RAM copy of the uboot code
 */
#define CONFIG_SYS_MALLOC_LEN	(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE 128	/* bytes reserved for initial data  */

/* Console configuration */
#define CONFIG_CONS_INDEX	1
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*
 * Command line configuration
 */
#include <config_cmd_default.h>

#undef CONFIG_CMD_BOOTD
#undef CONFIG_CMD_FLASH
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS

/*
 * Environment organization
 */
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_OVERWRITE

/*
 * Low Level Configuration Options
 * (depends on platform configuration)
 */

/* RAM: SRAM and SDRAM */
#define CONFIG_NR_DRAM_BANKS		1	/* We have 1 bank of SDRAM  */
#define CONFIG_SYS_SRAM_BASE		(PHYS_SRAM_PA)
#define CONFIG_SYS_SRAM_SIZE		(PHYS_SRAM_SIZE)

/* Serial Console (UART) */
#define CONFIG_SYS_NS16550		1
#define CONFIG_SYS_NS16550_SERIAL	1
#define CONFIG_SYS_NS16550_REG_SIZE	1

#if !CONFIG_OXNAS_UART

#define CONFIG_SYS_NS16550_CLK		16000000
#define CONFIG_SYS_NS16550_COM1		0x28000000

#else

#define CONFIG_SYS_NS16550_CLK		((CONFIG_OXNAS_PLL400_CLK) / 4)

#if (CONFIG_OXNAS_UART == 1)

#define CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CONFIG_SYS_NS16550_COM1		(UART_1_BASE_PA)

#elif (CONFIG_OXNAS_UART == 2)

#undef CONFIG_OXNAS_UART1
#define CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CONFIG_SYS_NS16550_COM1		(UART_2_BASE_PA)

#elif (CONFIG_OXNAS_UART == 3)

#undef CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#define CONFIG_OXNAS_UART3
#undef CONFIG_OXNAS_UART4
#define CONFIG_SYS_NS16550_COM1		(UART_3_BASE_PA)

#else

#undef CONFIG_OXNAS_UART1
#undef CONFIG_OXNAS_UART2
#undef CONFIG_OXNAS_UART3
#define CONFIG_OXNAS_UART4
#define CONFIG_SYS_NS16550_COM1		(UART_4_BASE_PA)

#endif

#endif

#endif /* __CONFIG_H */
