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

#include <asm/hardware.h>
#include <asm/io.h>

#if defined(CONFIG_DISPLAY_BOARDINFO)
int checkboard (void)
{
	char  buf[32];

        printf("\nOxSemi OXNAS %s\n\n", CONFIG_OXNAS_TEST_BRD
					? "test board"
					: "generic platform");

        return 0;
}
#endif

int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	/* arch number of OXNAS-Board */
	gd->bd->bi_arch_number = MACH_TYPE_OXNAS;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1_PA + 0x100;
	gd->flags = 0;

	/* speeds up your boot a quite a bit */
	icache_enable();

	return 0;
}
