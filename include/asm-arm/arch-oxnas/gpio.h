/*
 * OXE800 and OXE810: GPIO Function MUX
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

#ifndef __ASM_ARCH_OXNAS_GPIO_H
#define __ASM_ARCH_OXNAS_GPIO_H

#include <asm/arch/bitfield.h>

/*
 * General Purpose I/O Map
 *
 * come from Linux kernel source code:
 *   include/asm-arm/arch-oxnas/GPIO_PST_FunctionEnables.inc
 *
 * GPIO	|	1st		|	2nd		|	3rd
 * -----+--------------------------------------------------------------------
 *   0	| O:SYSPCI_GNT_N0	| O:SYSPCI_REQ_OUT_N	| I:UART3_RI_N
 *   1	| O:SYSPCI_GNT_N1	| I:SYSPCI_GNT_IN_N	| I:UART3_CD_N
 *   2	| O:SYSPCI_GNT_N2	| I:PCI_IDSEL		| I:UART3_CTS_N
 *   3	| O:SYSPCI_GNT_N3	| I:IRRX_IN		| I:UART3_DSR_N
 *   4	| I:SYSPCI_REQ_N0	| 			| O:UART3_DTR_N
 *   5	| I:SYSPCI_REQ_N1	| O:FAN_PWM3		| O:UART3_RTS_N
 *   6	| I:SYSPCI_REQ_N2	| I:AUDIO_TX_BITCK	| I:UART3_SIN
 *   7	| I:SYSPCI_REQ_N3	| I:AUDIO_TXLRCK	| O:UART3_SOUT
 *   8	| O:PCI_CKO		| O:FAN_PWM2		| I:UART2_DSR_N
 *   9	| 			| 			| O:UART2_RTS_N
 *  10	| 			| O:USB_CKO		|
 *  11	| O:PCI_CKO3		| 			|
 *  12	| O:STATIC_OE_N		| B:PCI_CCLKRUN_N	|
 *  13	| O:STATIC_ADDR21	| I:PCI_LOCK_N		|
 *  14	| O:STATIC_ADDR20	| B:PCI_PERR_N		|
 *  15	| O:STATIC_ADDR19	| O:PCI_SERR_N		|
 *  16	| O:STATIC_ADDR18	| O:MEM_DLLTGL		|
 *  17	| O:STATIC_ADDR17	| O:SATA_OBS_RBC0	|
 *  18	| O:STATIC_ADDR16	| O:PCI_CINT_N		|
 *  19	| O:STATIC_CS_N0	| O:PCI_CSTSCHG_N	|
 *  20	| O:STATIC_CS_N1	| 			| O:UART2_SOUT
 *  21	| O:STATIC_WE_N0	| 			|
 *  22	| O:STATIC_WE_N1	| 			| I:UART2_SIN
 *  23	| O:USBA_PWRO		| O:PCI_CKO		| I:UART2_RI_N
 *  24	| I:USBA_OVERI		| 			| I:UART2_CD_N
 *  25	| O:USBB_PWRO		| O:AUDIO_TXD0		| O:UART2_DTR_N
 *  26	| I:USBB_OVERI		| I:AUDIO_RXD0		| I:UART2_CTS_N
 *  27	| O:USBC_PWRO		| I:AUDIO_RXLRCK	| O:UART1_RTS_N
 *  28	| I:USBC_OVERI		| I:AUDIO_RX_BITCK	| I:UART1_CTS_N
 *  29	| B:FAN_TEMP		| O:AUDIO_TXD2		| I:UART1_DSR_N
 *  30	| I:FAN_TACHO		| I:AUDIO_RXD2		| I:UART1_CD_N
 *  31	| O:FAN_PWM0		| O:AUDIO_TXD3		| O:UART1_SOUT
 *  32	| O:FAN_PWM1		| I:AUDIO_RXD3		| I:UART1_SIN
 *  33	| B:IBIW_D		| I:AUDIO_RXD1		| I:UART1_RI_N
 *  34	| O:IBIW_LED		| O:AUDIO_TXD1		| O:UART1_DTR_N
 */


/* GPIO number */
#define GPIO_NUM_MASK		_BM(8, 0)

/* GPIO pin function */
#define GPIO_FN_MASK		_BM(2, 12)
#define GPIO_FN(VAL)		_BSV(VAL, 12, GPIO_FN_MASK)
#define GPIO_FN_F1ST		GPIO_FN(1)	/* 1st function enable */
#define GPIO_FN_F2ND		GPIO_FN(2)	/* 2nd function enable */
#define GPIO_FN_F3RD		GPIO_FN(3)	/* 3rd function enable */

/* GPIO pin direction */
#define GPIO_DIR_MASK		_BM(2, 14)
#define GPIO_DIR(VAL)		_BSV(VAL, 14, GPIO_DIR_MASK)
#define GPIO_DIR_IN		GPIO_DIR(1)	/* input */
#define GPIO_DIR_OUT		GPIO_DIR(2)	/* output */
#define GPIO_DIR_INOUT		GPIO_DIR(3)	/* bidirectional */

/*
 * GPIO Primary Function Enables
 */
#define GPIO_FN_1ST_SYSPCI_GNT_N0	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 0)
#define GPIO_FN_1ST_SYSPCI_GNT_N1	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 1)
#define GPIO_FN_1ST_SYSPCI_GNT_N2	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 2)
#define GPIO_FN_1ST_SYSPCI_GNT_N3	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 3)
#define GPIO_FN_1ST_SYSPCI_REQ_N0	(GPIO_DIR_IN    | GPIO_FN_F1ST | 4)
#define GPIO_FN_1ST_SYSPCI_REQ_N1	(GPIO_DIR_IN    | GPIO_FN_F1ST | 5)
#define GPIO_FN_1ST_SYSPCI_REQ_N2	(GPIO_DIR_IN    | GPIO_FN_F1ST | 6)
#define GPIO_FN_1ST_SYSPCI_REQ_N3	(GPIO_DIR_IN    | GPIO_FN_F1ST | 7)
#define GPIO_FN_1ST_PCI_CKO		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 8)
/* 2nd function on GPIO 9 is unknown */
/* 2nd function on GPIO 10 is unknown */
#define GPIO_FN_1ST_PCI_CKO3		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 11)
#define GPIO_FN_1ST_STATIC_OE_N		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 12)
#define GPIO_FN_1ST_STATIC_ADDR21	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 13)
#define GPIO_FN_1ST_STATIC_ADDR20	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 14)
#define GPIO_FN_1ST_STATIC_ADDR19	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 15)
#define GPIO_FN_1ST_STATIC_ADDR18	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 16)
#define GPIO_FN_1ST_STATIC_ADDR17	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 17)
#define GPIO_FN_1ST_STATIC_ADDR16	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 18)
#define GPIO_FN_1ST_STATIC_CS_N0	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 19)
#define GPIO_FN_1ST_STATIC_CS_N1	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 20)
#define GPIO_FN_1ST_STATIC_WE_N0	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 21)
#define GPIO_FN_1ST_STATIC_WE_N1	(GPIO_DIR_OUT   | GPIO_FN_F1ST | 22)
#define GPIO_FN_1ST_USBA_PWRO		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 23)
#define GPIO_FN_1ST_USBA_OVERI		(GPIO_DIR_IN    | GPIO_FN_F1ST | 24)
#define GPIO_FN_1ST_USBB_PWRO		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 25)
#define GPIO_FN_1ST_USBB_OVERI		(GPIO_DIR_IN    | GPIO_FN_F1ST | 26)
#define GPIO_FN_1ST_USBC_PWRO		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 27)
#define GPIO_FN_1ST_USBC_OVERI		(GPIO_DIR_IN    | GPIO_FN_F1ST | 28)
#define GPIO_FN_1ST_FAN_TEMP		(GPIO_DIR_INOUT | GPIO_FN_F1ST | 29)
#define GPIO_FN_1ST_FAN_TACHO		(GPIO_DIR_IN    | GPIO_FN_F1ST | 30)
#define GPIO_FN_1ST_FAN_PWM0		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 31)
#define GPIO_FN_1ST_FAN_PWM1		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 32)
#define GPIO_FN_1ST_IBIW_D		(GPIO_DIR_INOUT | GPIO_FN_F1ST | 33)
#define GPIO_FN_1ST_IBIW_LED		(GPIO_DIR_OUT   | GPIO_FN_F1ST | 34)

/*
 * GPIO Secondary Function Enables
 */
#define GPIO_FN_2ND_SYSPCI_REQ_OUT_N	(GPIO_DIR_OUT   | GPIO_FN_F2ND | 0)
#define GPIO_FN_2ND_SYSPCI_GNT_IN_N	(GPIO_DIR_IN    | GPIO_FN_F2ND | 1)
#define GPIO_FN_2ND_PCI_IDSEL		(GPIO_DIR_IN    | GPIO_FN_F2ND | 2)
#define GPIO_FN_2ND_IRRX_IN		(GPIO_DIR_IN    | GPIO_FN_F2ND | 3)
/* 2nd function on GPIO 4 is unknown */
#define GPIO_FN_2ND_FAN_PWM3		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 5)
#define GPIO_FN_2ND_AUDIO_TX_BITCK	(GPIO_DIR_IN    | GPIO_FN_F2ND | 6)
#define GPIO_FN_2ND_AUDIO_TXLRCK	(GPIO_DIR_IN    | GPIO_FN_F2ND | 7)
#define GPIO_FN_2ND_FAN_PWM2		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 8)
/* 2nd function on GPIO 9 is unknown */
#define GPIO_FN_2ND_USB_CKO		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 10)
/* 2nd function on GPIO 11 is unknown */
#define GPIO_FN_2ND_PCI_CCLKRUN_N	(GPIO_DIR_INOUT | GPIO_FN_F2ND | 12)
#define GPIO_FN_2ND_PCI_LOCK_N		(GPIO_DIR_IN    | GPIO_FN_F2ND | 13)
#define GPIO_FN_2ND_PCI_PERR_N		(GPIO_DIR_INOUT | GPIO_FN_F2ND | 14)
#define GPIO_FN_2ND_PCI_SERR_N		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 15)
#define GPIO_FN_2ND_MEM_DLLTGL		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 16)
#define GPIO_FN_2ND_SATA_OBS_RBC0	(GPIO_DIR_OUT   | GPIO_FN_F2ND | 17)
#define GPIO_FN_2ND_PCI_CINT_N		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 18)
#define GPIO_FN_2ND_PCI_CSTSCHG_N	(GPIO_DIR_OUT   | GPIO_FN_F2ND | 19)
/* 2nd function on GPIO 20 is unknown */
/* 2nd function on GPIO 21 is unknown */
/* 2nd function on GPIO 22 is unknown */
#define GPIO_FN_2ND_PCI_CKO		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 23)
/* 2nd function on GPIO 24 is unknown */
#define GPIO_FN_2ND_AUDIO_TXD0		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 25)
#define GPIO_FN_2ND_AUDIO_RXD0		(GPIO_DIR_IN    | GPIO_FN_F2ND | 26)
#define GPIO_FN_2ND_AUDIO_RXLRCK	(GPIO_DIR_IN    | GPIO_FN_F2ND | 27)
#define GPIO_FN_2ND_AUDIO_RX_BITCK	(GPIO_DIR_IN    | GPIO_FN_F2ND | 28)
#define GPIO_FN_2ND_AUDIO_TXD2		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 29)
#define GPIO_FN_2ND_AUDIO_RXD2		(GPIO_DIR_IN    | GPIO_FN_F2ND | 30)
#define GPIO_FN_2ND_AUDIO_TXD3		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 31)
#define GPIO_FN_2ND_AUDIO_RXD3		(GPIO_DIR_IN    | GPIO_FN_F2ND | 32)
#define GPIO_FN_2ND_AUDIO_RXD1		(GPIO_DIR_IN    | GPIO_FN_F2ND | 33)
#define GPIO_FN_2ND_AUDIO_TXD1		(GPIO_DIR_OUT   | GPIO_FN_F2ND | 34)

/*
 * GPIO Tertiary Function Enables
 */
#define GPIO_FN_3RD_UART3_RI_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 0)
#define GPIO_FN_3RD_UART3_CD_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 1)
#define GPIO_FN_3RD_UART3_CTS_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 2)
#define GPIO_FN_3RD_UART3_DSR_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 3)
#define GPIO_FN_3RD_UART3_DTR_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 4)
#define GPIO_FN_3RD_UART3_RTS_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 5)
#define GPIO_FN_3RD_UART3_SIN		(GPIO_DIR_IN    | GPIO_FN_F3RD | 6)
#define GPIO_FN_3RD_UART3_SOUT		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 7)
#define GPIO_FN_3RD_UART2_DSR_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 8)
#define GPIO_FN_3RD_UART2_RTS_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 9)
/* 3rd function on GPIO 10 is unknown */
/* 3rd function on GPIO 11 is unknown */
/* 3rd function on GPIO 12 is unknown */
/* 3rd function on GPIO 13 is unknown */
/* 3rd function on GPIO 14 is unknown */
/* 3rd function on GPIO 15 is unknown */
/* 3rd function on GPIO 16 is unknown */
/* 3rd function on GPIO 17 is unknown */
/* 3rd function on GPIO 18 is unknown */
/* 3rd function on GPIO 19 is unknown */
#define GPIO_FN_3RD_UART2_SOUT		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 20)
/* 3rd function on GPIO 21 is unknown */
#define GPIO_FN_3RD_UART2_SIN		(GPIO_DIR_IN    | GPIO_FN_F3RD | 22)
#define GPIO_FN_3RD_UART2_RI_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 23)
#define GPIO_FN_3RD_UART2_CD_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 24)
#define GPIO_FN_3RD_UART2_DTR_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 25)
#define GPIO_FN_3RD_UART2_CTS_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 26)
#define GPIO_FN_3RD_UART1_RTS_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 27)
#define GPIO_FN_3RD_UART1_CTS_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 28)
#define GPIO_FN_3RD_UART1_DSR_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 29)
#define GPIO_FN_3RD_UART1_CD_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 30)
#define GPIO_FN_3RD_UART1_SOUT		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 31)
#define GPIO_FN_3RD_UART1_SIN		(GPIO_DIR_IN    | GPIO_FN_F3RD | 32)
#define GPIO_FN_3RD_UART1_RI_N		(GPIO_DIR_IN    | GPIO_FN_F3RD | 33)
#define GPIO_FN_3RD_UART1_DTR_N		(GPIO_DIR_OUT   | GPIO_FN_F3RD | 34)

#endif /* __ASM_ARCH_OXNAS_GPIO_H */
