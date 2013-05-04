/*
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

#ifndef __ASM_ARCH_SYS_PROTO_H
#define __ASM_ARCH_SYS_PROTO_H

#include <asm/arch/hardware.h>

unsigned long get_cpu_clk_rate(void);
unsigned long get_sys_clk_rate(void);
unsigned long get_rps_clk_rate(void);
void set_clk_rate(unsigned long main_clock, unsigned long pll_clock);
void per_resetclocks_enable(void);

unsigned long probe_sdr_size(void);

void gpio_set_af(int gpio, int alternate_function);
void gpio_set_dir(int gpio, int direction);
void gpio_set_fn(int gpio_function);
void gpio_set(int gpio, int val);
int gpio_get(int gpio);

void set_muxconf_regs(void);

#endif /* __ASM_ARCH_SYS_PROTO_H */
