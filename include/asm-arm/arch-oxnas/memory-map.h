/*
 * Hardware definitions for OXE800 and OXE810
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __ASM_ARCH_MEMORYMAP_H
#define __ASM_ARCH_MEMORYMAP_H

#include <asm/sizes.h>

/*
 * Physical Memory Map
 *
 * come from Linux kernel source code:
 *   include/asm-arm/arch-oxnas/hardware.h
 *   arch/arm/mach-oxnas/oxnas.c
 *   arch/arm/mach-oxnas/dma.c
 *   arch/arm/mach-oxnas/pci.c
 *
 * 0x10000000	  4 kB	Internal Core Module
 * 0x40000000	 16 kB	Internal Boot ROM
 * 0x40200000	  4 MB	USB
 * 0x40400000	  4 MB	GEMAC
 * 0x40600000	  4 kB	PCI Command and Status Registers (CSRS)
 * 0x40800000	512 kB	PCI Non-prefetchable Memory
 * 0x40880000	512 kB	PCI Prefetchable Memory
 * 0x41000000	  4 kB	Static Bus Slot for CS0
 * 0x41400000	  4 kB	Static Bus Slot for CS1
 * 0x41800000	  4 kB	Static Bus Slot for CS2
 * 0x41C00000	  4 kB	Static Bus Controller
 * 0x42000000		SATA Data Transfer (16x32 bit DMA FIFO Channel)
 * 0x43000000		DPE Rx/Tx Cipher Core (16x32 bit DMA FIFO Channel)
 * 0x44000000	 16 MB	Advanced Peripheral Bus (APB) bridge A
 * + 0x000000		  General Purpose I/O (GPIO 1)
 * + 0x100000		  General Purpose I/O (GPIO 2)
 * + 0x200000		  Universal Asynchronous Receiver Transmitter (UART 1)
 * + 0x300000		  Universal Asynchronous Receiver Transmitter (UART 2)
 * + 0x400000		  Inter-Integrated Circuit (I2C)
 * + 0x500000		  Inter-IC Sound Interface (I2S)
 * + 0x600000		  Fan monitor (FMON)
 * + 0x700000		  Pulse wide modulation (PWM)
 * + 0x800000		  Infrared Receive (IRRX)
 * + 0x900000		  Universal Asynchronous Receiver Transmitter (UART 3)
 * + 0xA00000		  Universal Asynchronous Receiver Transmitter (UART 4)
 * 0x45000000	 16 MB	Advanced Peripheral Bus (APB) bridge B
 * + 0x000000		  System block reset and clock control (SYSCTRL)
 * + 0x100000		  Clock control (CLKCTRL)
 * + 0x200000		  Real time clock (RTC)
 * + 0x300000		  Reset and Pause controller (RPS)
 *    + 0x000		    RPS Interrupt controller
 *    + 0x100		    RPS Fast interrupt controller
 *    + 0x200		    RPS Timer 1
 *    + 0x220		    RPS Timer 2
 *    + 0x300		    RPS remap and pause
 *    + 0x3C0		    RPS GPIO (ex. Chip ID)
 * + 0x400000		  LEON CoProcessor RPS
 * + 0x500000		  AHB monitor
 *  + 0x00000		    ARM D-cache
 *  + 0x10000		    ARM I-cache
 *  + 0x20000		    DMA channel A
 *  + 0x30000		    DMA channel B
 *  + 0x40000		    LEON CoProcessor
 *  + 0x50000		    USB
 *  + 0x60000		    GMAC
 *  + 0x70000		    PCI
 * + 0x600000		  Direct memory access control (DMA)
 * + 0x700000		  Cipher Core (DPE)
 * + 0x780000		  Cipher Core (IBW)
 * + 0x800000		  DDR SDRAM control (DDRCTRL)
 * + 0x900000		  Serial-ATA (SATA 0/1)
 *  + 0x00000		    SATA0 register (OXE800/OXE810)
 *  + 0x10000		    SATA1 register (OXE810)
 *  + 0x40000		    SATA0 link register (OXE800)
 *  + 0x80000		    SATA0 register (OXE800)
 *  + 0xC0000		    SATA0 link register (OXE800)
 *  + 0xE0000		    SATA core register (OXE810)
 *  + 0xF0000		    SATA RAID register (OXE810)
 * + 0xA00000		  Direct memory access checksum (DMA)
 * + 0xB00000		  LEON CoProcessor registers
 * + 0xC00000		  Direct memory access SG (DMA)
 * 0x48000000	256 MB	SDRAM
 * 0x58000000	128 kB	SRAM (internal)
 * 0x58020000	4/8 kB	LEON CoProcessor Image Slot (internal)
 * 0x58040000	4/8 kB	LEON CoProcessor Image Slot (internal)
 */


/* Internal Core Components */
#define CORE_MODULE_BASE_PA	0x10000000

/* Internal Boot ROM */
#define ROM_BASE_PA		0x40000000
#define PHYS_ROM_PA		(ROM_BASE_PA)
#define PHYS_ROM_SIZE		(3 * SZ_16K)

/* High-Speed Core Components */
#define USB_BASE_PA		0x40200000
#define MAC_BASE_PA		0x40400000
#define PCI_CSRS_BASE_PA	0x40600000
#define PCI_BASE_PA		0x40800000

/* Static Bus Slots */
#define STATIC_CS0_BASE_PA	0x41000000
#define STATIC_CS1_BASE_PA	0x41400000
#define STATIC_CS2_BASE_PA	0x41800000
#define STATIC_CONTROL_BASE_PA	0x41C00000

/* DMA FIFO Endpoints */
#define SATA_DATA_BASE_PA	0x42000000
#define DPE_BASE_PA		0x43000000

/* Advanced Peripheral Bus (APB) */
#define APB_BRIDGE_A_BASE_PA	0x44000000
#define APB_BRIDGE_B_BASE_PA	0x45000000

/* RAM: SRAM and SDRAM */
#define PHYS_SDRAM_1_PA		0x48000000		/* SDRAM Bank #1    */
#define PHYS_SDRAM_1_MAX_SIZE	(SZ_256M)		/* max. 256MB       */
#define PHYS_SRAM_PA		((PHYS_SDRAM_1_PA) + (PHYS_SDRAM_1_MAX_SIZE))
#define PHYS_SRAM_SIZE		(SZ_128K)		/* SRAM have 128kB  */

/* ROM fetchable addresses */
#define ROM_REVISION			((PHYS_ROM_PA + PHYS_ROM_SIZE) - 0x4)

/* GPIO core peripheral addresses */
#define GPIO_1_BASE_PA			((APB_BRIDGE_A_BASE_PA) + 0x0)
#define GPIO_2_BASE_PA			((APB_BRIDGE_A_BASE_PA) + 0x100000)

#define GPIO_OFFS_DATA			0x0  /* (input/read back) data */
#define GPIO_OFFS_OE			0x4  /* output enable */
#define GPIO_OFFS_IE			0x8  /* INT enable */
#define GPIO_OFFS_IEVENT		0xC  /* INT event */
#define GPIO_OFFS_OUT			0x10 /* output (data) */
#define GPIO_OFFS_SET_OUT		0x14 /* set output (data) */
#define GPIO_OFFS_CLR_OUT		0x18 /* clear output (data) */
#define GPIO_OFFS_SET_OE		0x1C /* set output enable */
#define GPIO_OFFS_CLR_OE		0x20 /* clear output enable */
#define GPIO_OFFS_IN_DEB		0x24 /* input debounce enable */
#define GPIO_OFFS_IREAHE		0x28 /* INT rising edge, active high */
#define GPIO_OFFS_IFEALE		0x2C /* INT falling edge, active low */
#define GPIO_OFFS_IREDET		0x30 /* INT rising edge detected */
#define GPIO_OFFS_IFEDET		0x34 /* INT falling edge detected */
#define GPIO_OFFS_ILE			0x3C /* INT level detection enable */
#define GPIO_OFFS_IS			0x3C /* INT status */

#define GPIO_1_DATA			((GPIO_1_BASE_PA) + (GPIO_OFFS_DATA))
#define GPIO_1_OE			((GPIO_1_BASE_PA) + (GPIO_OFFS_OE))
#define GPIO_1_IE			((GPIO_1_BASE_PA) + (GPIO_OFFS_IE))
#define GPIO_1_INT_EVENT		((GPIO_1_BASE_PA) + (GPIO_OFFS_IEVENT))
#define GPIO_1_OUT			((GPIO_1_BASE_PA) + (GPIO_OFFS_OUT))
#define GPIO_1_SET_OUT			((GPIO_1_BASE_PA) + (GPIO_OFFS_SET_OUT))
#define GPIO_1_CLR_OUT			((GPIO_1_BASE_PA) + (GPIO_OFFS_CLR_OUT))
#define GPIO_1_SET_OE			((GPIO_1_BASE_PA) + (GPIO_OFFS_SET_OE))
#define GPIO_1_CLR_OE			((GPIO_1_BASE_PA) + (GPIO_OFFS_CLR_OE))
#define GPIO_1_IN_DEBOUNCE		((GPIO_1_BASE_PA) + (GPIO_OFFS_IN_DEB))
#define GPIO_1_IREDGEHIGHE		((GPIO_1_BASE_PA) + (GPIO_OFFS_IREAHE))
#define GPIO_1_IFEDGELOWE		((GPIO_1_BASE_PA) + (GPIO_OFFS_IFEALE))
#define GPIO_1_IREDGEDET		((GPIO_1_BASE_PA) + (GPIO_OFFS_IREDET))
#define GPIO_1_IFEDGEDET		((GPIO_1_BASE_PA) + (GPIO_OFFS_IFEDET))
#define GPIO_1_ILEVELE			((GPIO_1_BASE_PA) + (GPIO_OFFS_ILE))
#define GPIO_1_IS			((GPIO_1_BASE_PA) + (GPIO_OFFS_IS))

#define GPIO_2_DATA			((GPIO_2_BASE_PA) + (GPIO_OFFS_DATA))
#define GPIO_2_OE			((GPIO_2_BASE_PA) + (GPIO_OFFS_OE))
#define GPIO_2_IE			((GPIO_2_BASE_PA) + (GPIO_OFFS_IE))
#define GPIO_2_INT_EVENT		((GPIO_2_BASE_PA) + (GPIO_OFFS_IEVENT))
#define GPIO_2_OUT			((GPIO_2_BASE_PA) + (GPIO_OFFS_OUT))
#define GPIO_2_SET_OUT			((GPIO_2_BASE_PA) + (GPIO_OFFS_SET_OUT))
#define GPIO_2_CLR_OUT			((GPIO_2_BASE_PA) + (GPIO_OFFS_CLR_OUT))
#define GPIO_2_SET_OE			((GPIO_2_BASE_PA) + (GPIO_OFFS_SET_OE))
#define GPIO_2_CLR_OE			((GPIO_2_BASE_PA) + (GPIO_OFFS_CLR_OE))
#define GPIO_2_IN_DEBOUNCE		((GPIO_2_BASE_PA) + (GPIO_OFFS_IN_DEB))
#define GPIO_2_IREDGEHIGHE		((GPIO_2_BASE_PA) + (GPIO_OFFS_IREAHE))
#define GPIO_2_IFEDGELOWE		((GPIO_2_BASE_PA) + (GPIO_OFFS_IFEALE))
#define GPIO_2_IREDGEDET		((GPIO_2_BASE_PA) + (GPIO_OFFS_IREDET))
#define GPIO_2_IFEDGEDET		((GPIO_2_BASE_PA) + (GPIO_OFFS_IFEDET))
#define GPIO_2_ILEVELE			((GPIO_2_BASE_PA) + (GPIO_OFFS_ILE))
#define GPIO_2_IS			((GPIO_2_BASE_PA) + (GPIO_OFFS_IS))

/* Serial Console (UART) */
#define UART_1_BASE_PA			(APB_BRIDGE_A_BASE_PA + 0x200000)
#define UART_2_BASE_PA			(APB_BRIDGE_A_BASE_PA + 0x300000)
#define UART_3_BASE_PA			(APB_BRIDGE_A_BASE_PA + 0x900000)
#define UART_4_BASE_PA			(APB_BRIDGE_A_BASE_PA + 0xA00000)

/* System core peripheral addresses */
#define SYS_CONTROL_BASE_PA		((APB_BRIDGE_B_BASE_PA) + 0x0)
#define RPS_BASE_PA			((APB_BRIDGE_B_BASE_PA) + 0x300000)
#define DMA_BASE_PA			((APB_BRIDGE_B_BASE_PA) + 0x600000)
#define DDR_CONTROL_BASE_PA		((APB_BRIDGE_B_BASE_PA) + 0x800000)

/* System block reset and clock control */
#define SYS_CTRL_USB11_CTRL		(SYS_CONTROL_BASE_PA + 0x00)
#define SYS_CTRL_PCI_CTRL0		(SYS_CONTROL_BASE_PA + 0x04)
#define SYS_CTRL_PCI_CTRL1		(SYS_CONTROL_BASE_PA + 0x08)
#define SYS_CTRL_GPIO_PRIMSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0x0C)
#define SYS_CTRL_GPIO_PRIMSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0x10)
#define SYS_CTRL_GPIO_SECSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0x14)
#define SYS_CTRL_GPIO_SECSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0x18)
#define SYS_CTRL_USB11_STAT		(SYS_CONTROL_BASE_PA + 0x1c)
#define SYS_CTRL_PCI_STAT		(SYS_CONTROL_BASE_PA + 0x20)
#define SYS_CTRL_CKEN_CTRL		(SYS_CONTROL_BASE_PA + 0x24)
#define SYS_CTRL_RSTEN_CTRL		(SYS_CONTROL_BASE_PA + 0x28)
#define SYS_CTRL_CKEN_SET_CTRL		(SYS_CONTROL_BASE_PA + 0x2C)
#define SYS_CTRL_CKEN_CLR_CTRL		(SYS_CONTROL_BASE_PA + 0x30)
#define SYS_CTRL_RSTEN_SET_CTRL		(SYS_CONTROL_BASE_PA + 0x34)
#define SYS_CTRL_RSTEN_CLR_CTRL		(SYS_CONTROL_BASE_PA + 0x38)
#define SYS_CTRL_USBHSMPH_CTRL		(SYS_CONTROL_BASE_PA + 0x40)
#define SYS_CTRL_USBHSMPH_STAT		(SYS_CONTROL_BASE_PA + 0x44)
#define SYS_CTRL_PLLSYS_CTRL		(SYS_CONTROL_BASE_PA + 0x48)
#define SYS_CTRL_SEMA_STAT		(SYS_CONTROL_BASE_PA + 0x4C)
#define SYS_CTRL_SEMA_SET_CTRL		(SYS_CONTROL_BASE_PA + 0x50)
#define SYS_CTRL_SEMA_CLR_CTRL		(SYS_CONTROL_BASE_PA + 0x54)
#define SYS_CTRL_SEMA_MASKA_CTRL	(SYS_CONTROL_BASE_PA + 0x58)
#define SYS_CTRL_SEMA_MASKB_CTRL	(SYS_CONTROL_BASE_PA + 0x5C)
#define SYS_CTRL_SEMA_MASKC_CTRL	(SYS_CONTROL_BASE_PA + 0x60)
#define SYS_CTRL_CKCTRL_CTRL		(SYS_CONTROL_BASE_PA + 0x64)
#define SYS_CTRL_COPRO_CTRL		(SYS_CONTROL_BASE_PA + 0x68)
#define SYS_CTRL_PLLSYS_KEY_CTRL	(SYS_CONTROL_BASE_PA + 0x6C)
#define SYS_CTRL_GMAC_CTRL		(SYS_CONTROL_BASE_PA + 0x78)
#define SYS_CTRL_USBHSPHY_CTRL		(SYS_CONTROL_BASE_PA + 0x84)
#define SYS_CTRL_GPIO_TERTSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0x8C)
#define SYS_CTRL_GPIO_TERTSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0x90)
#define SYS_CTRL_UART_CTRL		(SYS_CONTROL_BASE_PA + 0x94)
#define SYS_CTRL_GPIO_PWMSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0x9C)
#define SYS_CTRL_GPIO_PWMSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0xA0)
#define SYS_CTRL_GPIO_MONSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0xA4)
#define SYS_CTRL_GPIO_MONSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0xA8)
#define SYS_CTRL_GPIO_PULLUP_CTRL_0	(SYS_CONTROL_BASE_PA + 0xAC)
#define SYS_CTRL_GPIO_PULLUP_CTRL_1	(SYS_CONTROL_BASE_PA + 0xB0)
#define SYS_CTRL_GPIO_ODRIVEHI_CTRL_0	(SYS_CONTROL_BASE_PA + 0xB4)
#define SYS_CTRL_GPIO_ODRIVEHI_CTRL_1	(SYS_CONTROL_BASE_PA + 0xB8)
#define SYS_CTRL_GPIO_ODRIVELO_CTRL_0	(SYS_CONTROL_BASE_PA + 0xBC)
#define SYS_CTRL_GPIO_ODRIVELO_CTRL_1	(SYS_CONTROL_BASE_PA + 0xC0)

/* RPS Timer core peripheral addresses */
#define RPS_TIMER_1_BASE_PA		(RPS_BASE_PA + 0x200)
#define RPS_TIMER_2_BASE_PA		(RPS_BASE_PA + 0x220)

#define RPS_TIMER_1_LOAD		(RPS_TIMER_1_BASE_PA + 0x0)
#define RPS_TIMER_1_VALUE		(RPS_TIMER_1_BASE_PA + 0x4)
#define RPS_TIMER_1_CONTROL		(RPS_TIMER_1_BASE_PA + 0x8)
#define RPS_TIMER_1_CLEAR		(RPS_TIMER_1_BASE_PA + 0xc)

#define RPS_TIMER_2_LOAD		(RPS_TIMER_2_BASE_PA + 0x0)
#define RPS_TIMER_2_VALUE		(RPS_TIMER_2_BASE_PA + 0x4)
#define RPS_TIMER_2_CONTROL		(RPS_TIMER_2_BASE_PA + 0x8)
#define RPS_TIMER_2_CLEAR		(RPS_TIMER_2_BASE_PA + 0xc)

/* RPS GPIO core peripheral addresses */
#define RPS_GPIO_BASE_PA		(RPS_BASE_PA + 0x3C0)

#define RPS_GPIO_OUT			(RPS_GPIO_BASE_PA + 0x0)
#define RPS_GPIO_OE			(RPS_GPIO_BASE_PA + 0x4)
#define RPS_GPIO_CHIPID			(RPS_GPIO_BASE_PA + 0x3C)

/* DDR controller */
#define DDR_CTRL_CFG			(DDR_CONTROL_BASE_PA + 0x00)
#define DDR_CTRL_BLKEN			(DDR_CONTROL_BASE_PA + 0x04)
#define DDR_CTRL_STAT			(DDR_CONTROL_BASE_PA + 0x08)
#define DDR_CTRL_CMD			(DDR_CONTROL_BASE_PA + 0x0C)
#define DDR_CTRL_AHB			(DDR_CONTROL_BASE_PA + 0x10)
#define DDR_CTRL_DLL			(DDR_CONTROL_BASE_PA + 0x14)
#define DDR_CTRL_MON			(DDR_CONTROL_BASE_PA + 0x18)
#define DDR_CTRL_DIAG			(DDR_CONTROL_BASE_PA + 0x1C)
#define DDR_CTRL_DIAG2			(DDR_CONTROL_BASE_PA + 0x20)
#define DDR_CTRL_IOC			(DDR_CONTROL_BASE_PA + 0x24)
#define DDR_CTRL_ARB			(DDR_CONTROL_BASE_PA + 0x28)
#define DDR_CTRL_AHB2			(DDR_CONTROL_BASE_PA + 0x2C)
#define DDR_CTRL_BUSY			(DDR_CONTROL_BASE_PA + 0x30)
#define DDR_CTRL_TIMING0		(DDR_CONTROL_BASE_PA + 0x34)
#define DDR_CTRL_TIMING1		(DDR_CONTROL_BASE_PA + 0x38)
#define DDR_CTRL_TIMING2		(DDR_CONTROL_BASE_PA + 0x3C)
#define DDR_CTRL_AHB3			(DDR_CONTROL_BASE_PA + 0x40)
#define DDR_CTRL_AHB4			(DDR_CONTROL_BASE_PA + 0x44)
#define DDR_CTRL_PHY0			(DDR_CONTROL_BASE_PA + 0x48)
#define DDR_CTRL_PHY1			(DDR_CONTROL_BASE_PA + 0x4C)
#define DDR_CTRL_PHY2			(DDR_CONTROL_BASE_PA + 0x50)
#define DDR_CTRL_PHY3			(DDR_CONTROL_BASE_PA + 0x54)

#endif /* __ASM_ARCH_MEMORYMAP_H */
