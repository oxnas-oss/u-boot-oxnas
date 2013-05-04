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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

#include <asm/arch/hardware.h>
#include <asm/arch/io.h>

static unsigned long cpu_clk_rate_hz;	/* ARMCLK */
static unsigned long sys_clk_rate_hz;	/* SYSCLK */
static unsigned long rps_clk_rate_hz;	/* RPSCLK */

unsigned long get_cpu_clk_rate(void)
{
	return cpu_clk_rate_hz;
}

unsigned long get_sys_clk_rate(void)
{
	return sys_clk_rate_hz;
}

unsigned long get_rps_clk_rate(void)
{
	return rps_clk_rate_hz;
}

void set_clk_rate(unsigned long main_clock, unsigned long pll_clock)
{
#if (CONFIG_OXNAS_FPGA == 1)
	cpu_clk_rate_hz = main_clock;
#else
	cpu_clk_rate_hz = pll_clock / 2;
#endif
	sys_clk_rate_hz = pll_clock / 4;
	rps_clk_rate_hz = main_clock;
}

void per_resetclocks_enable(void)
{
	/* Static Bus block reset */
	writel(SYS_CTRL_RSTEN_STATIC, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_STATIC, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Static Bus core clock enable */
	writel(SYS_CTRL_CKEN_STATIC, SYS_CTRL_CKEN_SET_CTRL);

	/* PCI block reset */
	writel(SYS_CTRL_RSTEN_PCI, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_PCI, SYS_CTRL_RSTEN_CLR_CTRL);

	/* PCI core clock enable */
	writel(SYS_CTRL_CKEN_PCI, SYS_CTRL_CKEN_SET_CTRL);

#ifdef CONFIG_OXNAS_UART1
	/* UART1 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART1, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART1, SYS_CTRL_RSTEN_CLR_CTRL);
#endif

#ifdef CONFIG_OXNAS_UART2
	/* UART2 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART2, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART2, SYS_CTRL_RSTEN_CLR_CTRL);
#endif

#ifdef CONFIG_OXNAS_UART3
	/* UART3 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART3, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART3, SYS_CTRL_RSTEN_CLR_CTRL);
#endif

#ifdef CONFIG_OXNAS_UART4
	/* UART4 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART4, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART4, SYS_CTRL_RSTEN_CLR_CTRL);
#endif
}
