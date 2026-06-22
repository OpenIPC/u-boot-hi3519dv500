# Copyright (c) CompanyNameMagicTag. 2021-2021. All rights reserved.
# Description:
# Author: AuthorNameMagicTag
# Create: 2021-03-05

ifeq ($(TOPDIR),)
TOPDIR   := $(realpath $(dir $(lastword $(MAKEFILE_LIST)))/../../../../..)
endif
DDR_TOP_DIR := $(TOPDIR)/drivers/ddr/vendor

EXTRA_CFLAGS += -I$(DDR_TOP_DIR)/boot_adaptation/uboot/ \
	-I$(DDR_TOP_DIR)/boot_adaptation/common/ \
	-I$(DDR_TOP_DIR)/include \
	-I$(DDR_TOP_DIR)/include/hal/chip/$(SOC)/ \
	-I$(DDR_TOP_DIR)/include/hal/ddrc \
	-I$(DDR_TOP_DIR)/include/hal/ddrt \
	-I$(DDR_TOP_DIR)/include/hal/phy

obj-y   := ddrtrn_uboot_cmd_loc.o
obj-y   += ddrtrn_uboot_cmd_ctl.o
obj-y   += ddrtrn_cmd_parsing.o
obj-y   += ../common/ddrtrn_boot.o
obj-y   += ../../training/ddrtrn_phy.o
obj-y   += ../../hal/phy/common/ddrtrn_hal_phy.o
obj-y   += ../../hal/phy/common/ddrtrn_hal_phy_common.o

obj-y   += ../../hal/chip/$(SOC)/ddrtrn_training_custom.o
obj-y   += ../../hal/chip/$(SOC)/ddrtrn_suspend_resume.o
obj-y   += ../../hal/chip/$(SOC)/ddrtrn_low_freq.o

ifeq ($(SOC), hi3519dv500)
obj-y   += ../../hal/phy/ddrtrn_hal_phy_c28_v200.o
else
$(error "Not support soc!!!" $(SOC) "end")
endif

