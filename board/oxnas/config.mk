#
# image should be loaded at 0x01000000
#

TEXT_BASE = 0x48d00000
CROSS_COMPILE = arm-linux-

# Define the master clock frequencies of the NAS chip - allow overriding from make invocation cmd line
PLL400 ?= 400000000
RPSCLK ?= 25000000
DDR_MEM ?= 1
RECOVERY_IMAGE ?= 1

PLATFORM_CPPFLAGS += -DNOMINAL_PLL400_FREQ=$(PLL400) -DNOMINAL_RPSCLK_FREQ=$(RPSCLK) -DSDRAM_IS_DDR=$(DDR_MEM) -DOXNAS_RECOVERY_IMAGE=$(RECOVERY_IMAGE)
