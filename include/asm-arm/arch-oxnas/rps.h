/*
 * OXE800 and OXE810: Reset and Pause controller (RPS)
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

#ifndef __ASM_ARCH_OXNAS_RPS_H
#define __ASM_ARCH_OXNAS_RPS_H

#include <asm/arch/bitfield.h>

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

#endif /* __ASM_ARCH_OXNAS_RPS_H */
