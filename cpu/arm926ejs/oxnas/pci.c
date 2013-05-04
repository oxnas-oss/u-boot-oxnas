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

void pci_bus_init (void)
{
	/* Assert manual arbitration request between Static Bus and PCI */
	writel(readl(SYS_CTRL_PCI_CTRL1) | SYS_CTRL_CKEN_PCI,
			SYS_CTRL_PCI_CTRL1);

	/* Set 33MHz PCI clock */
	writel(SYS_CTRL_CKCTRL_PCI_DIV(5), SYS_CTRL_CKCTRL_CTRL);

	/* Enable full speed RPS clock */
	writel(readl(SYS_CTRL_CKCTRL_CTRL) & ~SYS_CTRL_CKCTRL_SLOW,
					SYS_CTRL_CKCTRL_CTRL);
}
