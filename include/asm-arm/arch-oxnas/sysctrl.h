/*
 * OXE800 and OXE810: System block reset and clock control (SYSCTRL)
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

#ifndef __ASM_ARCH_OXNAS_SYSCTRL_H
#define __ASM_ARCH_OXNAS_SYSCTRL_H

#include <asm/arch/bitfield.h>

/* Bits in SYS_CTRL_PCI_CTRL1 */
#define SYS_CTRL_PCI_CTRL1_APP_CSTSCHG_N	_BV(0)
#define SYS_CTRL_PCI_CTRL1_APP_CBUS_INT_N	_BV(1)
#define SYS_CTRL_PCI_CTRL1_APP_EQUIES_NOM_CLK	_BV(2)
#define SYS_CTRL_PCI_CTRL1_INT_STATUS_0		_BV(3)
#define SYS_CTRL_PCI_CTRL1_SS_INT_MASK_0	_BV(4)
#define SYS_CTRL_PCI_CTRL1_SS_MINIPCI_EN	_BV(5)
#define SYS_CTRL_PCI_CTRL1_SS_CADBUS_EN		_BV(6)
#define SYS_CTRL_PCI_CTRL1_SYSPCI_PAKING_MASTER	_BV(7)
#define SYS_CTRL_PCI_CTRL1_SYSPCI_PAKING_EN	_BV(9)
#define SYS_CTRL_PCI_CTRL1_SS_HOST_EN		_BV(10)
#define SYS_CTRL_PCI_CTRL1_SYSPCI_STATIC_REQ	_BV(11)
#define SYS_CTRL_PCI_CTRL1_ENCB			_BV(12)
#define SYS_CTRL_PCI_CTRL1_ENPU			_BV(13)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO0		_BV(14)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO1		_BV(15)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO2		_BV(16)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO3		_BV(17)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO4		_BV(18)
#define SYS_CTRL_PCI_CTRL1_ENPU_GPIO5		_BV(19)

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

#endif /* __ASM_ARCH_OXNAS_SYSCTRL_H */
