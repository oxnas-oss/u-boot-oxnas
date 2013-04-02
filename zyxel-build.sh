#!/bin/sh

echo -e "Image file is \033[33mu-boot.bin\033[0m"
usage()
{
	echo "Usage: $0 { NSA210 | nsa210 | NSA221 | nsa221 | telia210 | TELIA210 }"
}

if [ -z "$1" ]; then
	usage
	exit 0
fi

if [ "$1" == "NSA210" -o "$1" == "nsa210" ]; then
	make oxnas_config CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=NSA210
	make CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=NSA210

	exit 0
fi

if [ "$1" == "NSA221" -o "$1" == "nsa221" ]; then
	make oxnas_config CROSS_COMPILE=/opt/sdk3.3-genericfs-arm-mv5sft/cross/bin/arm-mv5sft-linux-gnueabi- MODEL=NSA221
	make CROSS_COMPILE=/opt/sdk3.3-genericfs-arm-mv5sft/cross/bin/arm-mv5sft-linux-gnueabi- MODEL=NSA221

	exit 0
fi

if [ "$1" == "COVENTRYNSA221" ]; then
	make oxnas_config CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=COVENTRYNSA221
	make CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=COVENTRYNSA221

	exit 0
fi

if [ "$1" == "COVENTRYNSA210" ]; then
	make oxnas_config CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=COVENTRYNSA210
	make CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=COVENTRYNSA210

	exit 0
fi

if [ "$1" == "TELIA210" -o "$1" == "telia210" ]; then
	make oxnas_config CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=TELIA210
	make CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=TELIA210

	exit 0
fi


usage
exit 0
