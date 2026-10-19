# Retired: hi3519dv500 is built in OpenIPC/u-boot

This repository is archived. Hi3519DV500 (and the Hi3516DV500 die) U-Boot is
now built from the same tree as every other HiSilicon and Goke SoC OpenIPC
supports: the `openipc-hisilicon` branch of
[OpenIPC/u-boot](https://github.com/OpenIPC/u-boot/tree/openipc-hisilicon)
(OpenIPC/u-boot#32), with its CI on the `openipc` branch (OpenIPC/u-boot#34).

What changed for the boot images:

- The same names, `boot-hi3519dv500-dmeb-nor.bin` and
  `boot-hi3519dv500-dmebpro-nor.bin`, published to the
  [OpenIPC/firmware `latest`](https://github.com/OpenIPC/firmware/releases/tag/latest)
  release, which they replaced there.
- The OpenIPC boot layer shared with the other SoCs: the flash layout found at
  boot (512k boot, 256k env at 0x80000, firmware from 0xc0000, including the
  split NOR image), the environment kept in SPI NOR, and DRAM measured up to
  2 GiB rather than assumed to be 512 MiB.

The history here stays readable for reference.
