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

#include <asm/io.h>
#include <asm/hardware.h>

static void static_bus_init (void);
static void internal_uart_init (void);

#if defined(CONFIG_DISPLAY_BOARDINFO)
int checkboard (void)
{
	char  buf[32];

        printf("OxSemi OXE%u (%s) at %s MHz%s\n", CONFIG_OXNAS_CHIP,
			CONFIG_OXNAS_FPGA ? "FPGA" : "ASIC",
			strmhz(buf, CONFIG_OXNAS_ARMCLK),
			CONFIG_OXNAS_TEST_BRD ? ", test board" : "");
	printf("Local Bus at %s MHz\n", strmhz(buf, CONFIG_OXNAS_SYSCLK));
	printf("RPS Block at %s MHz\n", strmhz(buf, CFG_OXNAS_RPSCLK));

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

	static_bus_init();
	internal_uart_init();
	return 0;
}

static void static_bus_init (void)
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

	/* Assert manual arbitration request between Static Bus and PCI */
	writel(readl(SYS_CTRL_PCI_CTRL1) | SYS_CTRL_CKEN_PCI,
			SYS_CTRL_PCI_CTRL1);

	/* Set PCI feedback clk GPIO pin as an output */
	writel(readl(GPIO_1_SET_OE) | GPIOFMUX_1ST_PCI_CKO3, GPIO_1_SET_OE);

	/* Enable PCI feedback clk out 3 onto GPIO pin (output) */
	writel(readl(SYS_CTRL_GPIO_PRIMSEL_CTRL_0) | GPIOFMUX_1ST_PCI_CKO3,
			SYS_CTRL_GPIO_PRIMSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_SECSEL_CTRL_0) & ~GPIOFMUX_1ST_PCI_CKO3,
			SYS_CTRL_GPIO_SECSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_TERTSEL_CTRL_0) & ~GPIOFMUX_1ST_PCI_CKO3,
			SYS_CTRL_GPIO_TERTSEL_CTRL_0);

	/* Set 33MHz PCI clock */
	writel(SYS_CTRL_CKCTRL_PCI_DIV(5), SYS_CTRL_CKCTRL_CTRL);

	/* Enable full speed RPS clock */
	writel(readl(SYS_CTRL_CKCTRL_CTRL) & ~SYS_CTRL_CKCTRL_SLOW,
					SYS_CTRL_CKCTRL_CTRL);
}

static void internal_uart_init (void)
{
#ifdef CONFIG_OXNAS_UART1
	/* UART1 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART1, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART1, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Setup pin mux'ing for UART1 SOUT onto external pins */
	writel(readl(SYS_CTRL_GPIO_PRIMSEL_CTRL_0) & ~GPIOFMUX_3RD_UART1_SOUT,
			SYS_CTRL_GPIO_PRIMSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_SECSEL_CTRL_0) & ~GPIOFMUX_3RD_UART1_SOUT,
			SYS_CTRL_GPIO_SECSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_TERTSEL_CTRL_0) | GPIOFMUX_3RD_UART1_SOUT,
			SYS_CTRL_GPIO_TERTSEL_CTRL_0);

	/* Setup pin mux'ing for UART1 SIN onto external pins */
	writel(readl(SYS_CTRL_GPIO_PRIMSEL_CTRL_1) & ~GPIOFMUX_3RD_UART1_SIN,
			SYS_CTRL_GPIO_PRIMSEL_CTRL_1);
	writel(readl(SYS_CTRL_GPIO_SECSEL_CTRL_1) & ~GPIOFMUX_3RD_UART1_SIN,
			SYS_CTRL_GPIO_SECSEL_CTRL_1);
	writel(readl(SYS_CTRL_GPIO_TERTSEL_CTRL_1) | GPIOFMUX_3RD_UART1_SIN,
			SYS_CTRL_GPIO_TERTSEL_CTRL_1);

	/* Setup pin output enable for UART2 SOUT as o/p and SIN as i/p */
	writel(readl(GPIO_1_SET_OE) | GPIOFMUX_3RD_UART1_SOUT, GPIO_1_SET_OE);
	writel(readl(GPIO_2_CLR_OE) | GPIOFMUX_3RD_UART1_SIN, GPIO_2_CLR_OE);
#endif

#ifdef CONFIG_OXNAS_UART2
	/* UART2 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART2, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART2, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Setup pin mux'ing for UART2 SOUT and SIN onto external pins */
	writel(readl(SYS_CTRL_GPIO_PRIMSEL_CTRL_0)
			& ~(GPIOFMUX_3RD_UART2_SOUT | GPIOFMUX_3RD_UART2_SIN),
			SYS_CTRL_GPIO_PRIMSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_SECSEL_CTRL_0)
			& ~(GPIOFMUX_3RD_UART2_SOUT | GPIOFMUX_3RD_UART2_SIN),
			SYS_CTRL_GPIO_SECSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_TERTSEL_CTRL_0)
			| (GPIOFMUX_3RD_UART2_SOUT | GPIOFMUX_3RD_UART2_SIN),
			SYS_CTRL_GPIO_TERTSEL_CTRL_0);

	/* Setup pin output enable for UART2 SOUT as o/p and SIN as i/p */
	writel(readl(GPIO_1_SET_OE) | GPIOFMUX_3RD_UART2_SOUT, GPIO_1_SET_OE);
	writel(readl(GPIO_1_CLR_OE) | GPIOFMUX_3RD_UART2_SIN, GPIO_1_CLR_OE);
#endif

#ifdef CONFIG_OXNAS_UART3
	/* UART3 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART3, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART3, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Setup pin mux'ing for UART3 SOUT and SIN onto external pins */
	writel(readl(SYS_CTRL_GPIO_PRIMSEL_CTRL_0)
			& ~(GPIOFMUX_3RD_UART3_SOUT | GPIOFMUX_3RD_UART3_SIN),
			SYS_CTRL_GPIO_PRIMSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_SECSEL_CTRL_0)
			& ~(GPIOFMUX_3RD_UART3_SOUT | GPIOFMUX_3RD_UART3_SIN),
			SYS_CTRL_GPIO_SECSEL_CTRL_0);
	writel(readl(SYS_CTRL_GPIO_TERTSEL_CTRL_0)
			| (GPIOFMUX_3RD_UART3_SOUT | GPIOFMUX_3RD_UART3_SIN),
			SYS_CTRL_GPIO_TERTSEL_CTRL_0);

	/* Setup pin output enable for UART3 SOUT as o/p and SIN as i/p */
	writel(readl(GPIO_1_SET_OE) | GPIOFMUX_3RD_UART3_SOUT, GPIO_1_SET_OE);
	writel(readl(GPIO_1_CLR_OE) | GPIOFMUX_3RD_UART3_SIN, GPIO_1_CLR_OE);
#endif

#ifdef CONFIG_OXNAS_UART4
	/* UART4 block reset (assert/deassert) */
	writel(SYS_CTRL_RSTEN_UART4, SYS_CTRL_RSTEN_SET_CTRL);
	writel(SYS_CTRL_RSTEN_UART4, SYS_CTRL_RSTEN_CLR_CTRL);

	/* Enable UART4 to override PCI functions onto GPIOs */
	writel(readl(SYS_CTRL_UART_CTRL) | SYS_CTRL_UART4_NOT_PCI_MODE,
			SYS_CTRL_UART_CTRL);
#endif
}

int dram_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_OXNAS_PROBE_MSIZE
	/*
	 * Determine the amount of SDRAM the DDR controller is
	 * configured for by the platform configuration in
	 * board/oxnas/platform-810.S
	 */
	int ddr_size_pow2 = (readl(DDR_CTRL_CFG) & DDR_CTRL_CFG_SIZE_MASK)
					>> DDR_CTRL_CFG_SIZE_BIT;

	gd->bd->bi_dram[0].size  = (1 << ddr_size_pow2) * SZ_1M;

	/*
	 * Do we really have 256M, or are we working around the DDR
	 * controller's problem with 128M size?
	 */
	if ((gd->bd->bi_dram[0].size >> 20) == 256) {

		writel(0xdeadbeef, PHYS_SDRAM_1_PA);
		writel(0xbaadf00d, PHYS_SDRAM_1_PA + SZ_128M);

		if (readl(PHYS_SDRAM_1_PA) != 0xdeadbeef)
			/*
			 * Detect wrong overwrite, it is a corrupted
			 * controller -- force set to 128M size.
			 */
			gd->bd->bi_dram[0].size  = SZ_128M;
	}
#else
	gd->bd->bi_dram[0].size = CONFIG_OXNAS_MSIZE;
#endif

	gd->bd->bi_dram[0].start = PHYS_SDRAM_1_PA;

#if defined(CFG_SRAM_BASE) && defined(CFG_SRAM_SIZE)
	gd->bd->bi_sramstart = CFG_SRAM_BASE;
	gd->bd->bi_sramsize = CFG_SRAM_SIZE;
#endif

	return 0;
}
