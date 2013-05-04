/*
 * (C) Copyright 2005
 * Oxford Semiconductor Ltd
 *
 * (C) Copyright 2009 Alessandro Rubini
 * parts from cpu/arm926ejs/nomadik/gpio.c
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

static unsigned long gpio_base[2] = {
	GPIO_1_BASE_PA,
	GPIO_2_BASE_PA
};

static unsigned long gpio_primsel_base[2] = {
	SYS_CTRL_GPIO_PRIMSEL_CTRL_0,
	SYS_CTRL_GPIO_PRIMSEL_CTRL_1
};

static unsigned long gpio_secsel_base[2] = {
	SYS_CTRL_GPIO_SECSEL_CTRL_0,
	SYS_CTRL_GPIO_SECSEL_CTRL_1
};

static unsigned long gpio_tertsel_base[2] = {
	SYS_CTRL_GPIO_TERTSEL_CTRL_0,
	SYS_CTRL_GPIO_TERTSEL_CTRL_1
};

static inline unsigned long gpio_to_base(int gpio)
{
	return gpio_base[gpio / 32];
}

static inline unsigned long gpio_to_primsel_base(int gpio)
{
	return gpio_primsel_base[gpio / 32];
}

static inline unsigned long gpio_to_secsel_base(int gpio)
{
	return gpio_secsel_base[gpio / 32];
}

static inline unsigned long gpio_to_tertsel_base(int gpio)
{
	return gpio_tertsel_base[gpio / 32];
}

static inline u32 gpio_to_bit(int gpio)
{
	return 1 << (gpio & 0x1f);
}

void gpio_set_af(int gpio, int alternate_function)
{
	unsigned long primsel_base = gpio_to_primsel_base(gpio);
	unsigned long secsel_base = gpio_to_secsel_base(gpio);
	unsigned long tertsel_base = gpio_to_tertsel_base(gpio);
	u32 bit = gpio_to_bit(gpio);

	if (alternate_function == GPIO_FN_F1ST) {

		writel(readl(secsel_base)  & ~bit, secsel_base);
		writel(readl(tertsel_base) & ~bit, tertsel_base);
		writel(readl(primsel_base) |  bit, primsel_base);

	} else if (alternate_function == GPIO_FN_F2ND) {

		writel(readl(primsel_base) & ~bit, primsel_base);
		writel(readl(tertsel_base) & ~bit, tertsel_base);
		writel(readl(secsel_base)  |  bit, secsel_base);

	} else if (alternate_function == GPIO_FN_F3RD) {

		writel(readl(primsel_base) & ~bit, primsel_base);
		writel(readl(secsel_base)  & ~bit, secsel_base);
		writel(readl(tertsel_base) |  bit, tertsel_base);

	} else
		debug("Error.. %s failed\n", __FUNCTION__);
}

void gpio_set_dir(int gpio, int direction)
{
	unsigned long base = gpio_to_base(gpio);
	u32 bit = gpio_to_bit(gpio);

	if (direction == GPIO_DIR_IN)
		writel(bit, base + GPIO_OFFS_CLR_OE);

	else if (direction == GPIO_DIR_OUT)
		writel(bit, base + GPIO_OFFS_SET_OE);

	else
		debug("Error.. %s failed\n", __FUNCTION__);
}

void gpio_set_fn(int gpio_function)
{
	int gpio = gpio_function & GPIO_NUM_MASK;
	int func = gpio_function & GPIO_FN_MASK;
	int dir = gpio_function & GPIO_DIR_MASK;

	gpio_set_af(gpio, func);
	gpio_set_dir(gpio, dir);
}

void gpio_set(int gpio, int val)
{
	unsigned long base = gpio_to_base(gpio);
	u32 bit = gpio_to_bit(gpio);

	if (val)
		writel(bit, base + GPIO_OFFS_SET_OUT);
	else
		writel(bit, base + GPIO_OFFS_CLR_OUT);
}

int gpio_get(int gpio)
{
	unsigned long base = gpio_to_base(gpio);
	u32 bit = gpio_to_bit(gpio);

	return readl(base + GPIO_OFFS_DATA) & bit;
}
