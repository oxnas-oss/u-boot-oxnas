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

/*
 * Determine the amount of SDRAM the DDR controller is
 * configured for by the platform configuration in
 * cpu/arm926ejs/oxnas/oxe810_lowlevel_init.S
 */
unsigned long probe_sdr_size(void)
{
#ifdef CONFIG_OXNAS_PROBE_MSIZE
	int ddr_size_pow2 = (readl(DDR_CTRL_CFG) & DDR_CTRL_CFG_SIZE_MASK)
				>> DDR_CTRL_CFG_SIZE_BIT;
	unsigned long dram_size = (1 << ddr_size_pow2) * SZ_1M;

	/*
	 * Do we really have 256M, or are we working around the DDR
	 * controller's problem with 128M size?
	 */
	if ((dram_size >> 20) == 256) {

		writel(0xdeadbeef, PHYS_SDRAM_1_PA);
		writel(0xbaadf00d, PHYS_SDRAM_1_PA + SZ_128M);

		/*
		 * Detect wrong overwrite, it is a corrupted
		 * controller -- force set to 128M size.
		 */
		if (readl(PHYS_SDRAM_1_PA) != 0xdeadbeef)
			dram_size  = SZ_128M;
	}

	return dram_size;
#else
	return CONFIG_OXNAS_MSIZE;
#endif
}
