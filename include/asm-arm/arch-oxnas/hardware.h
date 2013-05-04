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

#include <asm/arch/sizes.h>

#define _BV(BIT)		(1 << (BIT))
#define _BM(BITS, BIT)		((_BV(BITS) - 1) << BIT)
#define _BSV(VAL, BIT, MASK)	(((VAL) << (BIT)) & MASK)


/*
 * Static clock definition
 */
#ifndef	CFG_OXNAS_FPGA_ARMCLK
#define	CFG_OXNAS_FPGA_ARMCLK	25000000  /* OXE FPGA clock: 25.00 MHz      */
#endif
#ifndef	CFG_OXNAS_PLL400
#define	CFG_OXNAS_PLL400	733333333 /* OXE ASIC clock: 733.33 MHz     */
#endif
#ifndef	CFG_OXNAS_RPSCLK
#define	CFG_OXNAS_RPSCLK	25000000  /* OXE system clock: 25.00 MHz    */
#endif

/* Clock to the ARM/DDR */
#if !CONFIG_OXNAS_FPGA
#define CONFIG_OXNAS_ARMCLK	((CFG_OXNAS_PLL400) / 2)
#define CONFIG_OXNAS_SYSCLK	((CFG_OXNAS_PLL400) / 4)
#else
#define CONFIG_OXNAS_ARMCLK	(CFG_OXNAS_FPGA_ARMCLK)
#define CONFIG_OXNAS_SYSCLK	((CFG_OXNAS_PLL400) / 4)
#endif


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


/* Advanced Peripheral Bus (APB) */
#define APB_BRIDGE_A_BASE_PA	0x44000000
#define APB_BRIDGE_B_BASE_PA	0x45000000

/* RAM: SRAM and SDRAM */
#define PHYS_SDRAM_1_PA		0x48000000		/* SDRAM Bank #1    */
#define PHYS_SDRAM_1_MAX_SIZE	(SZ_256M)		/* max. 256MB       */
#define PHYS_SRAM_PA		((PHYS_SDRAM_1_PA) + (PHYS_SDRAM_1_MAX_SIZE))
#define PHYS_SRAM_SIZE		(SZ_128K)		/* SRAM have 128kB  */

/* GPIO core peripheral addresses */
#define GPIO_1_BASE_PA		((APB_BRIDGE_A_BASE_PA) + 0x0)
#define GPIO_2_BASE_PA		((APB_BRIDGE_A_BASE_PA) + 0x100000)

#define GPIO_1_OE		((GPIO_1_BASE_PA) + 0x4)
#define GPIO_1_SET_OE		((GPIO_1_BASE_PA) + 0x1C)
#define GPIO_1_CLR_OE		((GPIO_1_BASE_PA) + 0x20)

#define GPIO_2_OE		((GPIO_2_BASE_PA) + 0x4)
#define GPIO_2_SET_OE		((GPIO_2_BASE_PA) + 0x1C)
#define GPIO_2_CLR_OE		((GPIO_2_BASE_PA) + 0x20)

/* Serial Console (UART) */
#define UART_1_BASE_PA		(APB_BRIDGE_A_BASE_PA + 0x200000)
#define UART_2_BASE_PA		(APB_BRIDGE_A_BASE_PA + 0x300000)
#define UART_3_BASE_PA		(APB_BRIDGE_A_BASE_PA + 0x900000)
#define UART_4_BASE_PA		(APB_BRIDGE_A_BASE_PA + 0xA00000)

/* System core peripheral addresses */
#define SYS_CONTROL_BASE_PA	((APB_BRIDGE_B_BASE_PA) + 0x0)
#define RPS_BASE_PA		((APB_BRIDGE_B_BASE_PA) + 0x300000)
#define DMA_BASE_PA		((APB_BRIDGE_B_BASE_PA) + 0x600000)
#define DDR_CONTROL_BASE_PA	((APB_BRIDGE_B_BASE_PA) + 0x800000)

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
#define SYSCTRL_GPIO_MONSEL_CTRL_0	(SYS_CONTROL_BASE_PA + 0xA4)
#define SYSCTRL_GPIO_MONSEL_CTRL_1	(SYS_CONTROL_BASE_PA + 0xA8)
#define SYSCTRL_GPIO_PULLUP_CTRL_0	(SYS_CONTROL_BASE_PA + 0xAC)
#define SYSCTRL_GPIO_PULLUP_CTRL_1	(SYS_CONTROL_BASE_PA + 0xB0)
#define SYSCTRL_GPIO_ODRIVEHI_CTRL_0	(SYS_CONTROL_BASE_PA + 0xB4)
#define SYSCTRL_GPIO_ODRIVEHI_CTRL_1	(SYS_CONTROL_BASE_PA + 0xB8)
#define SYSCTRL_GPIO_ODRIVELO_CTRL_0	(SYS_CONTROL_BASE_PA + 0xBC)
#define SYSCTRL_GPIO_ODRIVELO_CTRL_1	(SYS_CONTROL_BASE_PA + 0xC0)

/* RPS Timer core peripheral addresses */
#define RPS_TIMER1			(RPS_BASE_PA + 0x200)
#define RPS_TIMER1_LOAD			(RPS_BASE_PA + 0x200)
#define RPS_TIMER1_VALUE		(RPS_BASE_PA + 0x204)
#define RPS_TIMER1_CONTROL		(RPS_BASE_PA + 0x208)
#define RPS_TIMER1_CLEAR		(RPS_BASE_PA + 0x20c)

#define RPS_TIMER2			(RPS_BASE_PA + 0x220)
#define RPS_TIMER2_LOAD			(RPS_BASE_PA + 0x220)
#define RPS_TIMER2_VALUE		(RPS_BASE_PA + 0x224)
#define RPS_TIMER2_CONTROL		(RPS_BASE_PA + 0x228)
#define RPS_TIMER2_CLEAR		(RPS_BASE_PA + 0x22c)

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

/* Bits in SYS_CTRL_PCI_CTRL1 */
#define SYS_CTL_PCI_CTRL1_APP_CSTSCHG_N		_BV(0)
#define SYS_CTL_PCI_CTRL1_APP_CBUS_INT_N	_BV(1)
#define SYS_CTL_PCI_CTRL1_APP_EQUIES_NOM_CLK	_BV(2)
#define SYS_CTL_PCI_CTRL1_INT_STATUS_0		_BV(3)
#define SYS_CTL_PCI_CTRL1_SS_INT_MASK_0		_BV(4)
#define SYS_CTL_PCI_CTRL1_SS_MINIPCI_EN		_BV(5)
#define SYS_CTL_PCI_CTRL1_SS_CADBUS_EN		_BV(6)
#define SYS_CTL_PCI_CTRL1_SYSPCI_PAKING_MASTER	_BV(7)
#define SYS_CTL_PCI_CTRL1_SYSPCI_PAKING_EN	_BV(9)
#define SYS_CTL_PCI_CTRL1_SS_HOST_EN		_BV(10)
#define SYS_CTL_PCI_CTRL1_SYSPCI_STATIC_REQ	_BV(11)
#define SYS_CTL_PCI_CTRL1_ENCB			_BV(12)
#define SYS_CTL_PCI_CTRL1_ENPU			_BV(13)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO0		_BV(14)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO1		_BV(15)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO2		_BV(16)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO3		_BV(17)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO4		_BV(18)
#define SYS_CTL_PCI_CTRL1_ENPU_GPIO5		_BV(19)

/* Bits in SYS_CTRL_CKEN_SET_CTRL and SYS_CTRL_CKEN_CLR_CTRL */
#define SYS_CTRL_CKEN_COPRO		_BV(0)
#define SYS_CTRL_CKEN_DMA		_BV(1)
#define SYS_CTRL_CKEN_DPE		_BV(2)
#define SYS_CTRL_CKEN_DDR_BIT		3
#define SYS_CTRL_CKEN_DDR		_BV(SYS_CTRL_CKEN_DDR_BIT)
#define SYS_CTRL_CKEN_SATA		_BV(4)
#define SYS_CTRL_CKEN_I2S		_BV(5)
#define SYS_CTRL_CKEN_USBHS		_BV(6)
#define SYS_CTRL_CKEN_MAC		_BV(7)
#define SYS_CTRL_CKEN_PCI		_BV(8)
#define SYS_CTRL_CKEN_STATIC		_BV(9)
#define SYS_CTRL_CKEN_DDR_PHY_BIT	10
#define SYS_CTRL_CKEN_DDR_PHY		_BV(SYS_CTRL_CKEN_DDR_PHY_BIT)

#define SYS_CTRL_CKEN_PONDEFAULT	(SYS_CTRL_CKEN_COPRO	| \
					 SYS_CTRL_CKEN_DMA	| \
					 SYS_CTRL_CKEN_DPE	| \
					 SYS_CTRL_CKEN_SATA	| \
					 SYS_CTRL_CKEN_I2S	| \
					 SYS_CTRL_CKEN_USBHS	| \
					 SYS_CTRL_CKEN_MAC	| \
					 SYS_CTRL_CKEN_STATIC)

/* Bits in SYS_CTRL_RSTEN_SET_CTRL and SYS_CTRL_RSTEN_CLR_CTRL */
#define SYS_CTRL_RSTEN_ARM		_BV(0)
#define SYS_CTRL_RSTEN_COPRO		_BV(1)
#define SYS_CTRL_RSTEN_USBHS		_BV(4)
#define SYS_CTRL_RSTEN_USBHSPHY		_BV(5)
#define SYS_CTRL_RSTEN_MAC		_BV(6)
#define SYS_CTRL_RSTEN_PCI		_BV(7)
#define SYS_CTRL_RSTEN_DMA		_BV(8)
#define SYS_CTRL_RSTEN_DPE		_BV(9)
#define SYS_CTRL_RSTEN_DDR_BIT		10
#define SYS_CTRL_RSTEN_DDR		_BV(SYS_CTRL_RSTEN_DDR_BIT)
#define SYS_CTRL_RSTEN_SATA		_BV(11)
#define SYS_CTRL_RSTEN_SATA_LINK	_BV(12)
#define SYS_CTRL_RSTEN_SATA_PHY		_BV(13)
#define SYS_CTRL_RSTEN_STATIC		_BV(15)
#define SYS_CTRL_RSTEN_GPIO		_BV(16)
#define SYS_CTRL_RSTEN_UART1		_BV(17)
#define SYS_CTRL_RSTEN_UART2		_BV(18)
#define SYS_CTRL_RSTEN_MISC		_BV(19)
#define SYS_CTRL_RSTEN_I2S		_BV(20)
#define SYS_CTRL_RSTEN_AHB_MON		_BV(21)
#define SYS_CTRL_RSTEN_UART3		_BV(22)
#define SYS_CTRL_RSTEN_UART4		_BV(23)
#define SYS_CTRL_RSTEN_SGDMA		_BV(24)
#define SYS_CTRL_RSTEN_DDR_PHY_BIT	25
#define SYS_CTRL_RSTEN_DDR_PHY		_BV(SYS_CTRL_RSTEN_DDR_PHY_BIT)
#define SYS_CTRL_RSTEN_BUS		_BV(31)

#define SYS_CTRL_RSTEN_PONDEFAULT	(SYS_CTRL_RSTEN_COPRO		| \
					 SYS_CTRL_RSTEN_USBHS		| \
					 SYS_CTRL_RSTEN_USBHSPHY	| \
					 SYS_CTRL_RSTEN_MAC		| \
					 SYS_CTRL_RSTEN_PCI		| \
					 SYS_CTRL_RSTEN_DMA		| \
					 SYS_CTRL_RSTEN_DPE		| \
					 SYS_CTRL_RSTEN_SATA		| \
					 SYS_CTRL_RSTEN_SATA_LINK	| \
					 SYS_CTRL_RSTEN_SATA_PHY	| \
					 SYS_CTRL_RSTEN_STATIC		| \
					 SYS_CTRL_RSTEN_UART1		| \
					 SYS_CTRL_RSTEN_UART2		| \
					 SYS_CTRL_RSTEN_MISC		| \
					 SYS_CTRL_RSTEN_I2S		| \
					 SYS_CTRL_RSTEN_AHB_MON		| \
					 SYS_CTRL_RSTEN_UART3		| \
					 SYS_CTRL_RSTEN_UART4		| \
					 SYS_CTRL_RSTEN_SGDMA)

/* Bits in SYS_CTRL_PLLSYS_CTRL */
#define SYS_CTRL_PLLSYS_CTRL_BYPASS	_BV(17)

/* Bits in SYS_CTRL_CKCTRL_CTRL */
#define SYS_CTRL_CKCTRL_PCI_DIV_MASK	_BM(4, 0)
#define SYS_CTRL_CKCTRL_PCI_DIV(VAL)	_BSV(VAL, 0, \
						SYS_CTRL_CKCTRL_PCI_DIV_MASK)
#define SYS_CTRL_CKCTRL_SLOW		_BV(8)

/* Bits in SYS_CTRL_PLLSYS_KEY_CTRL */
#define SYS_CTRL_PLLSYS_KEY_CTRL_VALID	0xbeadface

/* Bits in SYS_CTRL_UART_CTRL */
#define SYS_CTRL_UART2_DEQ_EN		_BV(0)
#define SYS_CTRL_UART3_DEQ_EN		_BV(1)
#define SYS_CTRL_UART3_IQ_EN		_BV(2)
#define SYS_CTRL_UART4_IQ_EN		_BV(3)
#define SYS_CTRL_UART4_NOT_PCI_MODE	_BV(4)

/* Bits in RPS_TIMER(1|2)_LOAD and RPS_TIMER(1|2)_VALUE */
#define TIMER_VALUE_MASK		_BM(16, 0)

/* Bits in RPS_TIMER1_CONTROL and RPS_TIMER2_CONTROL */
#define TIMER_CTRL_PRESCALE_MASK	_BM(2, 2)
#define TIMER_CTRL_PRESCALE(VAL)	_BSV(VAL, 2, TIMER_CTRL_PRESCALE_MASK)

#define TPS_1				0
#define TPS_16				1
#define TPS_256				2

#define TIMER_CTRL_MODE_PERIODIC	_BV(6)
#define TIMER_CTRL_ENABLE		_BV(7)

/* Bits in DDR_CTRL_CFG */
#define DDR_CTRL_CFG_SDR		_BV(16)
#define DDR_CTRL_CFG_SIZE_BIT		17
#define DDR_CTRL_CFG_SIZE_MASK		_BM(4, DDR_CTRL_CFG_SIZE_BIT)
#define DDR_CTRL_CFG_SIZE_MBPO2(PO2)	_BSV(PO2, DDR_CTRL_CFG_SIZE_BIT, \
						DDR_CTRL_CFG_SIZE_MASK)
#define DDR_CTRL_CFG_BANKS_BIT		23
#define DDR_CTRL_CFG_BANKS		_BV(DDR_CTRL_CFG_BANKS_BIT)

#define PO2_1MB				0
#define PO2_2MB				1
#define PO2_4MB				2
#define PO2_8MB				3
#define PO2_16MB			4
#define PO2_32MB			5
#define PO2_64MB			6
#define PO2_128MB			7
#define PO2_256MB			8
#define PO2_512MB			9
#define PO2_1GB				10
#define PO2_2GB				11
#define PO2_4GB				12
#define PO2_8GB				13
#define PO2_16GB			14
#define PO2_32GB			15

/* Bits in DDR_CTRL_BLKEN */
#define DDR_CTRL_BLKEN_CLIENTS_MASK	_BM(16, 0)
#define DDR_CTRL_BLKEN_CLIENTS(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_BLKEN_CLIENTS_MASK)
#define DDR_CTRL_BLKEN_CORE		_BV(31)

/* Bits in DDR_CTRL_AHB */
#define DDR_CTRL_AHB_FLUSH_RCACHE_MASK	_BM(16,	0)
#define DDR_CTRL_AHB_FLUSH_RCACHE(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_AHB_FLUSH_RCACHE_MASK)

#define DDR_CTRL_AHB_FLUSH_RCACHE_ARMD	_BV(0)
#define DDR_CTRL_AHB_FLUSH_RCACHE_ARMI	_BV(1)
#define DDR_CTRL_AHB_FLUSH_RCACHE_COPRO	_BV(2)
#define DDR_CTRL_AHB_FLUSH_RCACHE_DMAA	_BV(3)
#define DDR_CTRL_AHB_FLUSH_RCACHE_DMAB	_BV(4)
#define DDR_CTRL_AHB_FLUSH_RCACHE_PCI	_BV(5)
#define DDR_CTRL_AHB_FLUSH_RCACHE_GMAC	_BV(6)
#define DDR_CTRL_AHB_FLUSH_RCACHE_USB	_BV(7)

#define DDR_CTRL_AHB_NO_RCACHE_MASK	_BM(16,	16)
#define DDR_CTRL_AHB_NO_RCACHE(VAL)	_BSV(VAL, 16, \
						DDR_CTRL_AHB_NO_RCACHE_MASK)

#define DDR_CTRL_AHB_NO_RCACHE_ARMD	_BV(16)
#define DDR_CTRL_AHB_NO_RCACHE_ARMI	_BV(17)
#define DDR_CTRL_AHB_NO_RCACHE_COPRO	_BV(18)
#define DDR_CTRL_AHB_NO_RCACHE_DMAA	_BV(19)
#define DDR_CTRL_AHB_NO_RCACHE_DMAB	_BV(20)
#define DDR_CTRL_AHB_NO_RCACHE_PCI	_BV(21)
#define DDR_CTRL_AHB_NO_RCACHE_GMAC	_BV(22)
#define DDR_CTRL_AHB_NO_RCACHE_USB	_BV(23)

/* Bits in DDR_CTRL_DLL */
#define DDR_CTRL_DLL_OFFSET_MASK	_BM(16,	0)
#define DDR_CTRL_DLL_OFFSET(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_DLL_OFFSET_MASK)
#define DDR_CTRL_DLL_AUTO		_BV(29)
#define DDR_CTRL_DLL_NOOFFS		_BV(30)
#define DDR_CTRL_DLL_ENABLE		_BV(31)

/* Bits in DDR_CTRL_MON */
#define DDR_CTRL_MON_CLIENT		_BV(0)
#define DDR_CTRL_MON_ALL		_BV(4)

/* Bits in DDR_CTRL_DIAG */
#define DDR_CTRL_DIAG_READS_MASK	_BM(10,	0)
#define DDR_CTRL_DIAG_READS(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_DIAG_READS_MASK)
#define DDR_CTRL_DIAG_WRITES_MASK	_BM(10,	10)
#define DDR_CTRL_DIAG_WRITES(VAL)	_BSV(VAL, 10, \
						DDR_CTRL_DIAG_WRITES_MASK)
#define DDR_CTRL_DIAG_HOLDOFFS_MASK	_BM(12,	20)
#define DDR_CTRL_DIAG_HOLDOFFS(VAL)	_BSV(VAL, 20, \
						DDR_CTRL_DIAG_HOLDOFFS_MASK)

/* Bits in DDR_CTRL_DIAG2 */
#define DDR_CTRL_DIAG2_DIRCHANGES_MASK	_BM(10,	0)
#define DDR_CTRL_DIAG2_DIRCHANGES(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_DIAG2_DIRCHANGES_MASK)

/* Bits in DDR_CTRL_ARB */
#define DDR_CTRL_ARB_DATDIR_NCH		_BV(0)
#define DDR_CTRL_ARB_DATDIR_EN		_BV(1)
#define DDR_CTRL_ARB_REQAGE_EN		_BV(2)
#define DDR_CTRL_ARB_LRUBANK_EN		_BV(3)
#define DDR_CTRL_ARB_MIDBUF		_BV(4)

/* Bits in DDR_CTRL_AHB2 */
#define DDR_CTRL_AHB2_IGNORE_HPROT_MASK	_BM(16,	0)
#define DDR_CTRL_AHB2_IGNORE_HPROT(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_AHB2_IGNORE_HPROT_MASK)

#define DDR_CTRL_AHB2_IGNORE_HPROT_ARMD	_BV(0)
#define DDR_CTRL_AHB2_IGNORE_HPROT_ARMI	_BV(1)
#define DDR_CTRL_AHB2_IGNORE_HPROT_COPRO _BV(2)
#define DDR_CTRL_AHB2_IGNORE_HPROT_DMAA	_BV(3)
#define DDR_CTRL_AHB2_IGNORE_HPROT_DMAB	_BV(4)
#define DDR_CTRL_AHB2_IGNORE_HPROT_PCI	_BV(5)
#define DDR_CTRL_AHB2_IGNORE_HPROT_GMAC	_BV(6)
#define DDR_CTRL_AHB2_IGNORE_HPROT_USB	_BV(7)

#define DDR_CTRL_AHB2_IGNORE_WRAP_MASK	_BM(16,	16)
#define DDR_CTRL_AHB2_IGNORE_WRAP(VAL)	_BSV(VAL, 16, \
						DDR_CTRL_AHB2_IGNORE_WRAP_MASK)

#define DDR_CTRL_AHB2_IGNORE_WRAP_ARMD	_BV(16)
#define DDR_CTRL_AHB2_IGNORE_WRAP_ARMI	_BV(17)
#define DDR_CTRL_AHB2_IGNORE_WRAP_COPRO	_BV(18)
#define DDR_CTRL_AHB2_IGNORE_WRAP_DMAA	_BV(19)
#define DDR_CTRL_AHB2_IGNORE_WRAP_DMAB	_BV(20)
#define DDR_CTRL_AHB2_IGNORE_WRAP_PCI	_BV(21)
#define DDR_CTRL_AHB2_IGNORE_WRAP_GMAC	_BV(22)
#define DDR_CTRL_AHB2_IGNORE_WRAP_USB	_BV(23)

/* Bits in DDR_CTRL_AHB3 */
#define DDR_CTRL_AHB3_DIS_BURST_MASK	_BM(16,	0)
#define DDR_CTRL_AHB3_DIS_BURST(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_AHB3_DIS_BURST_MASK)

#define DDR_CTRL_AHB3_DIS_BURST_ARMD	_BV(0)
#define DDR_CTRL_AHB3_DIS_BURST_ARMI	_BV(1)
#define DDR_CTRL_AHB3_DIS_BURST_COPRO	_BV(2)
#define DDR_CTRL_AHB3_DIS_BURST_DMAA	_BV(3)
#define DDR_CTRL_AHB3_DIS_BURST_DMAB	_BV(4)
#define DDR_CTRL_AHB3_DIS_BURST_PCI	_BV(5)
#define DDR_CTRL_AHB3_DIS_BURST_GMAC	_BV(6)
#define DDR_CTRL_AHB3_DIS_BURST_USB	_BV(7)

#define DDR_CTRL_AHB3_DIS_NONCACHE_MASK	_BM(16,	16)
#define DDR_CTRL_AHB3_DIS_NONCACHE(VAL)	_BSV(VAL, 16, \
						DDR_CTRL_AHB3_DIS_NONCACHE_MASK)

#define DDR_CTRL_AHB3_DIS_NONCACHE_ARMD	_BV(16)
#define DDR_CTRL_AHB3_DIS_NONCACHE_ARMI	_BV(17)
#define DDR_CTRL_AHB3_DIS_NONCACHE_COPRO _BV(18)
#define DDR_CTRL_AHB3_DIS_NONCACHE_DMAA	_BV(19)
#define DDR_CTRL_AHB3_DIS_NONCACHE_DMAB	_BV(20)
#define DDR_CTRL_AHB3_DIS_NONCACHE_PCI	_BV(21)
#define DDR_CTRL_AHB3_DIS_NONCACHE_GMAC	_BV(22)
#define DDR_CTRL_AHB3_DIS_NONCACHE_USB	_BV(23)

/* Bits in DDR_CTRL_AHB4 */
#define DDR_CTRL_AHB4_EN_TIMEOUT_MASK	_BM(16,	0)
#define DDR_CTRL_AHB4_EN_TIMEOUT(VAL)	_BSV(VAL, 0, \
						DDR_CTRL_AHB4_EN_TIMEOUT_MASK)

#define DDR_CTRL_AHB4_EN_TIMEOUT_ARMD	_BV(0)
#define DDR_CTRL_AHB4_EN_TIMEOUT_ARMI	_BV(1)
#define DDR_CTRL_AHB4_EN_TIMEOUT_COPRO	_BV(2)
#define DDR_CTRL_AHB4_EN_TIMEOUT_DMAA	_BV(3)
#define DDR_CTRL_AHB4_EN_TIMEOUT_DMAB	_BV(4)
#define DDR_CTRL_AHB4_EN_TIMEOUT_PCI	_BV(5)
#define DDR_CTRL_AHB4_EN_TIMEOUT_GMAC	_BV(6)
#define DDR_CTRL_AHB4_EN_TIMEOUT_USB	_BV(7)

#define DDR_CTRL_AHB4_EN_WRBEHIND_MASK	_BM(16,	16)
#define DDR_CTRL_AHB4_EN_WRBEHIND(VAL)	_BSV(VAL, 16, \
						DDR_CTRL_AHB4_EN_WRBEHIND_MASK)

#define DDR_CTRL_AHB4_EN_WRBEHIND_ARMD	_BV(16)
#define DDR_CTRL_AHB4_EN_WRBEHIND_ARMI	_BV(17)
#define DDR_CTRL_AHB4_EN_WRBEHIND_COPRO	_BV(18)
#define DDR_CTRL_AHB4_EN_WRBEHIND_DMAA	_BV(19)
#define DDR_CTRL_AHB4_EN_WRBEHIND_DMAB	_BV(20)
#define DDR_CTRL_AHB4_EN_WRBEHIND_PCI	_BV(21)
#define DDR_CTRL_AHB4_EN_WRBEHIND_GMAC	_BV(22)
#define DDR_CTRL_AHB4_EN_WRBEHIND_USB	_BV(23)

/*
 * GPIO Primary Function Enables
 */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_0, GPIO_1_SET_OE, and GPIO_1_CLR_OE    */
#define GPIOFMUX_1ST_SYSPCI_GNT_N0	_BV(0)	/*  as output        */
#define GPIOFMUX_1ST_SYSPCI_GNT_N1	_BV(1)	/*  as output        */
#define GPIOFMUX_1ST_SYSPCI_GNT_N2	_BV(2)	/*  as output        */
#define GPIOFMUX_1ST_SYSPCI_GNT_N3	_BV(3)	/*  as output        */
#define GPIOFMUX_1ST_SYSPCI_REQ_N0	_BV(4)	/*  as input         */
#define GPIOFMUX_1ST_SYSPCI_REQ_N1	_BV(5)	/*  as input         */
#define GPIOFMUX_1ST_SYSPCI_REQ_N2	_BV(6)	/*  as input         */
#define GPIOFMUX_1ST_SYSPCI_REQ_N3	_BV(7)	/*  as input         */
#define GPIOFMUX_1ST_PCI_CKO		_BV(8)	/*  as output        */
#define GPIOFMUX_1ST_PCI_CKO3		_BV(11)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_OE_N	_BV(12)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR21	_BV(13)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR20	_BV(14)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR19	_BV(15)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR18	_BV(16)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR17	_BV(17)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_ADDR16	_BV(18)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_CS_N0	_BV(19)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_CS_N1	_BV(20)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_WE_N0	_BV(21)	/*  as output        */
#define GPIOFMUX_1ST_STATIC_WE_N1	_BV(22)	/*  as output        */
#define GPIOFMUX_1ST_USBA_PWRO		_BV(23)	/*  as output        */
#define GPIOFMUX_1ST_USBA_OVERI		_BV(24)	/*  as input         */
#define GPIOFMUX_1ST_USBB_PWRO		_BV(25)	/*  as output        */
#define GPIOFMUX_1ST_USBB_OVERI		_BV(26)	/*  as input         */
#define GPIOFMUX_1ST_USBC_PWRO		_BV(27)	/*  as output        */
#define GPIOFMUX_1ST_USBC_OVERI		_BV(28)	/*  as input         */
#define GPIOFMUX_1ST_FAN_TEMP		_BV(29)	/*  is bidirectional */
#define GPIOFMUX_1ST_FAN_TACHO		_BV(30)	/*  as input         */
#define GPIOFMUX_1ST_FAN_PWM0		_BV(31)	/*  as output        */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_1, GPIO_2_SET_OE, and GPIO_2_CLR_OE    */
#define GPIOFMUX_1ST_FAN_PWM1		_BV(0)	/*  as output        */
#define GPIOFMUX_1ST_IBIW_D		_BV(1)	/*  is bidirectional */
#define GPIOFMUX_1ST_IBIW_LED		_BV(2)	/*  as output        */

/*
 * GPIO Secondary Function Enables
 */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_0, GPIO_1_SET_OE, and GPIO_1_CLR_OE    */
#define GPIOFMUX_2ND_SYSPCI_REQ_OUT_N	_BV(0)	/*  as output        */
#define GPIOFMUX_2ND_SYSPCI_GNT_IN_N	_BV(1)	/*  as input         */
#define GPIOFMUX_2ND_PCI_IDSEL		_BV(2)	/*  as input         */
#define GPIOFMUX_2ND_IRRX_IN		_BV(3)	/*  as input         */
#define GPIOFMUX_2ND_FAN_PWM3		_BV(5)	/*  as output        */
#define GPIOFMUX_2ND_AUDIO_TX_BITCK	_BV(6)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_TXLRCK	_BV(7)	/*  as input         */
#define GPIOFMUX_2ND_FAN_PWM2		_BV(8)	/*  as output        */
#define GPIOFMUX_2ND_USB_CKO		_BV(10)	/*  as output        */
#define GPIOFMUX_2ND_PCI_CCLKRUN_N	_BV(12)	/*  is bidirectional */
#define GPIOFMUX_2ND_PCI_LOCK_N		_BV(13)	/*  as input         */
#define GPIOFMUX_2ND_PCI_PERR_N		_BV(14)	/*  is bidirectional */
#define GPIOFMUX_2ND_PCI_SERR_N		_BV(15)	/*  as output        */
#define GPIOFMUX_2ND_MEM_DLLTGL		_BV(16)	/*  as output        */
#define GPIOFMUX_2ND_SATA_OBS_RBC0	_BV(17)	/*  as output        */
#define GPIOFMUX_2ND_PCI_CINT_N		_BV(18)	/*  as output        */
#define GPIOFMUX_2ND_PCI_CSTSCHG_N	_BV(19)	/*  as output        */
#define GPIOFMUX_2ND_PCI_CKO		_BV(23)	/*  as output        */
#define GPIOFMUX_2ND_AUDIO_TXD0		_BV(25)	/*  as output        */
#define GPIOFMUX_2ND_AUDIO_RXD0		_BV(26)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_RXLRCK	_BV(27)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_RX_BITCK	_BV(28)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_TXD2		_BV(29)	/*  as output        */
#define GPIOFMUX_2ND_AUDIO_RXD2		_BV(30)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_TXD3		_BV(31)	/*  as output        */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_1, GPIO_2_SET_OE, and GPIO_2_CLR_OE    */
#define GPIOFMUX_2ND_AUDIO_RXD3		_BV(0)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_RXD1		_BV(1)	/*  as input         */
#define GPIOFMUX_2ND_AUDIO_TXD1		_BV(2)	/*  as output        */

/*
 * GPIO Tertiary Function Enables
 */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_0, GPIO_1_SET_OE, and GPIO_1_CLR_OE    */
#define GPIOFMUX_3RD_UART3_RI_N		_BV(0)	/*  as input         */
#define GPIOFMUX_3RD_UART3_CD_N		_BV(1)	/*  as input         */
#define GPIOFMUX_3RD_UART3_CTS_N	_BV(2)	/*  as input         */
#define GPIOFMUX_3RD_UART3_DSR_N	_BV(3)	/*  as input         */
#define GPIOFMUX_3RD_UART3_DTR_N	_BV(4)	/*  as output        */
#define GPIOFMUX_3RD_UART3_RTS_N	_BV(5)	/*  as output        */
#define GPIOFMUX_3RD_UART3_SIN		_BV(6)	/*  as input         */
#define GPIOFMUX_3RD_UART3_SOUT		_BV(7)	/*  as output        */
#define GPIOFMUX_3RD_UART2_DSR_N	_BV(8)	/*  as input         */
#define GPIOFMUX_3RD_UART2_RTS_N	_BV(9)	/*  as output        */
#define GPIOFMUX_3RD_UART2_SOUT		_BV(20)	/*  as output        */
#define GPIOFMUX_3RD_UART2_SIN		_BV(22)	/*  as input         */
#define GPIOFMUX_3RD_UART2_RI_N		_BV(23)	/*  as input         */
#define GPIOFMUX_3RD_UART2_CD_N		_BV(24)	/*  as input         */
#define GPIOFMUX_3RD_UART2_DTR_N	_BV(25)	/*  as output        */
#define GPIOFMUX_3RD_UART2_CTS_N	_BV(26)	/*  as input         */
#define GPIOFMUX_3RD_UART1_RTS_N	_BV(27)	/*  as output        */
#define GPIOFMUX_3RD_UART1_CTS_N	_BV(28)	/*  as input         */
#define GPIOFMUX_3RD_UART1_DSR_N	_BV(29)	/*  as input         */
#define GPIOFMUX_3RD_UART1_CD_N		_BV(30)	/*  as input         */
#define GPIOFMUX_3RD_UART1_SOUT		_BV(31)	/*  as output        */
/* SYS_CTRL_GPIO_PRIMSEL_CTRL_1, GPIO_2_SET_OE, and GPIO_2_CLR_OE    */
#define GPIOFMUX_3RD_UART1_SIN		_BV(0)	/*  as input         */
#define GPIOFMUX_3RD_UART1_RI_N		_BV(1)	/*  as input         */
#define GPIOFMUX_3RD_UART1_DTR_N	_BV(2)	/*  as output        */

