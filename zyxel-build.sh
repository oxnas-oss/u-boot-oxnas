#!/bin/sh

usage()
{
	echo "Usage: $0 { NSA210 | nsa210 | NSA221 | nsa221 }"
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
	make oxnas_config CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=NSA221
	make CROSS_COMPILE=/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le- MODEL=NSA221

	exit 0
fi


usage
exit 0
