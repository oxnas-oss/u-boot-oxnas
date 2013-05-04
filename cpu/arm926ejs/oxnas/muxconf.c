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

void set_muxconf_regs(void)
{
	/*
	 * Enable PCI feedback clk out 3 onto GPIO pin (output). Set PCI
	 * feedback clk GPIO pin as an output.
	 */
	gpio_set_fn(GPIO_FN_1ST_PCI_CKO3);

	/*
	 * Setup pin mux'ing for UART1 SOUT and SIN onto external pins.
	 * Setup pin output enable for UART1 SOUT as output and SIN as input.
	 */
#ifdef CONFIG_OXNAS_UART1
	gpio_set_fn(GPIO_FN_3RD_UART1_SOUT);
	gpio_set_fn(GPIO_FN_3RD_UART1_SIN);
#endif

	/*
	 * Setup pin mux'ing for UART2 SOUT and SIN onto external pins.
	 * Setup pin output enable for UART2 SOUT as output and SIN as input.
	 */
#ifdef CONFIG_OXNAS_UART2
	gpio_set_fn(GPIO_FN_3RD_UART2_SOUT);
	gpio_set_fn(GPIO_FN_3RD_UART2_SIN);
#endif

	/*
	 * Setup pin mux'ing for UART3 SOUT and SIN onto external pins.
	 * Setup pin output enable for UART3 SOUT as output and SIN as input.
	 */
#ifdef CONFIG_OXNAS_UART3
	gpio_set_fn(GPIO_FN_3RD_UART3_SOUT);
	gpio_set_fn(GPIO_FN_3RD_UART3_SIN);
#endif

#ifdef CONFIG_OXNAS_UART4
	/* Enable UART4 to override PCI functions onto GPIOs */
	writel(readl(SYS_CTRL_UART_CTRL) | SYS_CTRL_UART4_NOT_PCI_MODE,
			SYS_CTRL_UART_CTRL);
#endif
}


