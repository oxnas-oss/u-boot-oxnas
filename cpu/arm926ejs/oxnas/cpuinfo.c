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
#include <asm/arch/sys_proto.h>

#if (CONFIG_OXNAS_CHIP == 810)

unsigned long system_serial_high;
unsigned long system_serial_low;

#define DIE_ID_ACK_LOCAL	(1UL << 0)
#define DIE_ID_BCK_LOCAL	(1UL << 1)
#define DIE_ID_FENB_LOCAL	(1UL << 5)
#define DIE_ID_SET_LOCAL	(1UL << 3)
#define DIE_ID_SEN_LOCAL	(1UL << 2)
#define DIE_ID_SDI_LOCAL	(1UL << 4)
#define DIE_ID_SDOUT_LOCAL	(1UL << 16)
#define DIE_ID_BITS		48
#define READBACK_BITS		32

/*
 * Read the 48-bit die-id stored in electrically fused (EFROM).
 *
 * The stored id is accessed via the RPS GPIO lines. The data is clocked out
 * serially, reconstructed, and written to the global uint_32t values that hold
 * the low and high serial id's.
 *
 * During the readout, it is possible to inject values into the EFROM that will
 * be read out after the first 48 die-id bits have been clocked out. This is
 * used to confirm the integrity of the die-id bits.
 *
 * References: Samsung SS90GRVLV_EFROM_HD V1.0
 *             OxSemi AMBA Sub-System Design Doc DD_B011A_AMBASys 2.0
 */
static void oxe810_read_die_id(void)
{
	unsigned int temp = 0;
	int i = 0;
	unsigned long long die_id = 0;
	unsigned long long readback = 0;
	unsigned long sdi = 0xbeefcafe;

	/* enable RPS GPIO outputs */
	temp = readl(RPS_GPIO_OE);
	temp |= (DIE_ID_SET_LOCAL | DIE_ID_FENB_LOCAL | DIE_ID_SEN_LOCAL);
	temp |= (DIE_ID_ACK_LOCAL | DIE_ID_BCK_LOCAL | DIE_ID_SDI_LOCAL);
	writel(temp, RPS_GPIO_OE);

	/* raise set */
	temp = DIE_ID_SET_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	/* raise fenb */
	temp |= DIE_ID_FENB_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	/* clear set */
	temp &= ~DIE_ID_SET_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	/* raise sense */
	temp |= DIE_ID_SEN_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	/* clear sense */
	temp &= ~DIE_ID_SEN_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	/* clear fenb */
	temp &= ~DIE_ID_FENB_LOCAL;
	writel(temp, RPS_GPIO_OUT);
	udelay(1);

	for (i = 0; i < (DIE_ID_BITS + READBACK_BITS); i++) {

		/* raise bclk */
		temp |= DIE_ID_BCK_LOCAL;
		writel(temp, RPS_GPIO_OUT);
		udelay(1);

		/* feed in predefined value for testing */
		if (sdi & (1ULL << i)) {
			temp |= DIE_ID_SDI_LOCAL;
		} else {
			temp &= ~DIE_ID_SDI_LOCAL;
		}

		writel(temp, RPS_GPIO_OUT);
		udelay(1);

		/* lower bclk */
		temp &= ~DIE_ID_BCK_LOCAL;
		writel(temp, RPS_GPIO_OUT);
		udelay(1);

		/* pulse ack */
		temp |= DIE_ID_ACK_LOCAL;
		writel(temp, RPS_GPIO_OUT);
		udelay(1);

		temp &= ~DIE_ID_ACK_LOCAL;
		writel(temp, RPS_GPIO_OUT);

		if (i >= DIE_ID_BITS) {
			readback |= (((unsigned long long)(readl(RPS_GPIO_OUT))
					& DIE_ID_SDOUT_LOCAL) << 16);
			readback >>= 1;
		} else {
			die_id |= (((unsigned long long)(readl(RPS_GPIO_OUT))
					& DIE_ID_SDOUT_LOCAL) << 32);
			die_id >>= 1;
		}
	}

	/* invert */
	die_id = ~die_id & 0xFFFFFFFFFFFFULL;
	readback = ~readback & (unsigned long long) ~0UL;

	if (readback == sdi) {
		system_serial_high = die_id >> 32;
		system_serial_low = die_id & ~0UL;
	} else {
		printf("Chip Id: Unexpected readback 0x%08llx\n", readback);
	}
}
#endif

static char *strascrev (char *buf, long ascrev)
{
	char *ascrevp = (void *)&ascrev;

	if (ascrevp[0] == '0')
		sprintf (buf, "v%c.%c%c", ascrevp[1],
				ascrevp[2], ascrevp[3]);
	else
		sprintf (buf, "v%c%c.%c%c", ascrevp[0],
				ascrevp[1], ascrevp[2], ascrevp[3]);

	return buf;
}

int print_cpuinfo(void)
{
	char buf[32];

	printf("CPU: %s", OXNAS_CPU_NAME);
	printf(" %s", strascrev(buf, readl(RPS_GPIO_CHIPID)));
	printf(", ROM: %s\n", strascrev(buf, readl(ROM_REVISION)));

#if (CONFIG_OXNAS_CHIP == 810)
	oxe810_read_die_id();
	printf("DID: %08lx%08lx\n", system_serial_high, system_serial_low);
#endif

	printf("\nCrystal frequency: %8s MHz\n",
			strmhz(buf, get_rps_clk_rate()));
	printf("CPU clock        : %8s MHz\n",
			strmhz(buf, get_cpu_clk_rate()));
	printf("Local Bus clock  : %8s MHz\n",
			strmhz(buf, get_sys_clk_rate()));

	return 0;
}
