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

#include <asm/arch/io.h>
#include <asm/arch/hardware.h>

void reset_cpu(ulong ignored)
{
	printf("Resetting Oxsemi NAS...");

	/* Assert reset to cores as per power on defaults */
	writel(SYS_CTRL_RSTEN_PONDEFAULT, SYS_CTRL_RSTEN_SET_CTRL);

	/* Release reset to cores as per power on defaults */
	writel(SYS_CTRL_RSTEN_GPIO, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Disable clocks to cores as per power-on defaults */
	writel(SYS_CTRL_CKEN_PONDEFAULT, SYS_CTRL_CKEN_CLR_CTRL);

	/* Enable clocks to cores as per power-on defaults */
	writel(SYS_CTRL_CKEN_PCI, SYS_CTRL_CKEN_SET_CTRL);

	/* Set sys-control pin mux'ing as per power-on defaults */
	writel(GPIOFMUX_1ST_PCI_CKO3, SYS_CTRL_GPIO_PRIMSEL_CTRL_0);
	writel(0x0UL, SYS_CTRL_GPIO_PRIMSEL_CTRL_1);
	writel(0x0UL, SYS_CTRL_GPIO_SECSEL_CTRL_0);
	writel(0x0UL, SYS_CTRL_GPIO_SECSEL_CTRL_1);
	writel(0x0UL, SYS_CTRL_GPIO_TERTSEL_CTRL_0);
	writel(0x0UL, SYS_CTRL_GPIO_TERTSEL_CTRL_1);

	/*
	 * No need to save any state, as the ROM loader can determine
	 * whether reset is due to power cycling or programatic action,
	 * just hit the (self-clearing) CPU reset bit of the block
	 * reset register
	 */
	writel(SYS_CTRL_RSTEN_ARM, SYS_CTRL_RSTEN_SET_CTRL);

	while (1);
	/* Never reached */
}
