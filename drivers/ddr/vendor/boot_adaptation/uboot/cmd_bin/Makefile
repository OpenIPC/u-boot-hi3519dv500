# Copyright (c) CompanyNameMagicTag. 2021-2021. All rights reserved.
# Description:
# Author: AuthorNameMagicTag
# Create: 2021-03-05

CUR_PATH := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
################################################################################

ifeq ($(TOPDIR),)
TOPDIR   := $(realpath $(dir $(lastword $(MAKEFILE_LIST)))/../../../../../../)
endif
sinclude $(TOPDIR)/arch/$(ARCH)/config.mk       # include architecture dependend rules

PWD      := $(shell pwd)
OPPDIR   := $(subst $(TOPDIR),,$(PWD))
DDR_TOP_DIR = $(realpath $(CUR_PATH)/../../..)
################################################################################
DDR_CMD     := ddr_cmd
sinclude $(TOPDIR)/include/config/auto.conf
ifneq ("$(MAKECMDGOALS)","clean")
CMD_TEXT_BASE := $(shell grep '^\#define.*DDR_TRAINING_RUN_STACK' $(DDR_TOP_DIR)/include/hal/chip/$(SOC)/ddrtrn_training_custom.h|awk '{print $$3}')
endif
STACK_POINT   := $(CMD_TEXT_BASE)

INCLUDE_DIR := -I$(TOPDIR)/include \
	-I$(TOPDIR)/arch/$(ARCH)/include \
	-I$(DDR_TOP_DIR)/include \
	-I$(DDR_TOP_DIR)/include/training \
	-I$(DDR_TOP_DIR)/include/hal/chip/$(SOC)/ \
	-I$(DDR_TOP_DIR)/include/hal/ddrc \
	-I$(DDR_TOP_DIR)/include/hal/ddrt \
	-I$(DDR_TOP_DIR)/include/hal/phy \
	-I$(DDR_TOP_DIR)/boot_adaptation/uboot/cmd_bin/ \
	-I$(DDR_TOP_DIR)/boot_adaptation/common

SRCS := $(wildcard $(DDR_TOP_DIR)/boot_adaptation/uboot/cmd_bin/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/boot_adaptation/common/ddrtrn_common_ctl.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/api/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/training/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/phy/common/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/ddrc/common/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/ddrt/common/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/sysctrl/*.c)
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/uart/*.c)

CFLAGS   := -Os -pipe  \
	-DCMD_TEXT_BASE=$(CMD_TEXT_BASE) \
	-DSTACK_POINT=$(STACK_POINT) \
	-DDDR_TRAINING_CMD \
	-D__KERNEL__ \
	-fno-builtin \
	-ffreestanding \
	-Wall -Werror \
	$(INCLUDE_DIR)
ifneq ($(LLVM), )
CFLAGS += -Wno-error=asm-operand-widths
endif
ifneq ("$(MAKECMDGOALS)","clean")
SRCS += $(wildcard $(DDR_TOP_DIR)/hal/chip/$(SOC)/*.c)
ifeq ($(SOC),hi3519dv500)
SRCS += $(DDR_TOP_DIR)/hal/phy/ddrtrn_hal_phy_c28_v200.c
SRCS += $(DDR_TOP_DIR)/hal/ddrc/ddrtrn_ddrc_s14.c
SRCS += $(DDR_TOP_DIR)/hal/ddrt/ddrtrn_hal_ddrt_v2_3.c
else
$(info "Not support SOC!!!" $(SOC) "end")
endif
endif

COBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(COBJS)) $(patsubst %.o,%.d,$(START))

ifneq ($(OBJTREE),$(SRCTREE))
CFLAGS += -I$(OBJTREE)/include2 -I$(OBJTREE)/include
endif
CFLAGS += $(PLATFORM_RELFLAGS) $(PLATFORM_CPPFLAGS)

ifeq ("$(CONFIG_ARM64)","y")
START       := ddrtrn_cmdbin_entry_64.o
LDS_SCRIPT := ddrtrn_cmdbin_64.lds
CFLAGS += -DCONFIG_ARM64
else
START       := ddrtrn_cmdbin_entry_32.o
LDS_SCRIPT := ddrtrn_cmdbin_32.lds
endif

################################################################################

LINK_FILES = $(SSRC)
.PHONY: $(DDR_CMD).bin
all: $(DDR_CMD).bin
	#remove soft link files
	@rm -f $(LINK_FILES) *.o *.d *.elf *.map *.srec

ifneq ($(LLVM), )
$(DDR_CMD).bin: $(DDR_CMD).elf
	$(OBJCOPY) -O binary $(PWD)/$(DDR_CMD).elf $@
else
$(DDR_CMD).bin: $(DDR_CMD).elf
	$(OBJCOPY) -O srec $(PWD)/$(DDR_CMD).elf $(DDR_CMD).srec
	$(OBJCOPY) --gap-fill=0xff -O binary $(PWD)/$(DDR_CMD).elf $@
endif
$(DDR_CMD).elf: $(START) $(COBJS) $(LDS_SCRIPT)
	$(LD) -Bstatic -T $(LDS_SCRIPT) -Ttext $(CMD_TEXT_BASE) $(START) \
		$(COBJS) $(AOBJS) -Map $(DDR_CMD).map -o $@

.PHONY: clean
clean:
	@rm -vf *.o *.d *.elf *.map *.srec $(LINK_FILES) $(DDR_CMD).bin

%.o : %.S
	$(CC) -D__ASSEMBLY__ $(CFLAGS) -o $@ -c $*.S

%.o : %.c
	$(CC) $(CFLAGS) -Wall -Wstrict-prototypes -fno-stack-protector \
		-o $@ -c $*.c

ifneq ("$(MAKECMDGOALS)","clean")
sinclude $(DEPS)
endif

%.d : %.c
	set -e; $(CC) $(CFLAGS) -MM $< | sed 's,$*.o:,$*.o $*.d:,g' > $@

%.d : %.S
	set -e; $(CC) $(CFLAGS) -MM $< | sed 's,$*.o:,$*.o $*.d:,g' > $@

################################################################################
