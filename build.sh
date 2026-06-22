#!/bin/bash
set -eo pipefail   # NB: `bash build.sh` ignores a shebang -e, so set it explicitly
# Build signed boot images for Hi3519DV500 (mirror of u-boot-hi3516cv6xx/build.sh,
# adapted for the ARMv8/aarch64 V5 SoC). Produces, per DDR binning:
#   output/boot-hi3519dv500-<binning>-nor.bin   (GSL-signed boot image, flash this)
#   output/smoke-hi3519dv500.bin                (raw u-boot-z, identical across binnings)
#
# Pipeline per binning: build hi-gzip -> build u-boot -> build GSL ->
#   image_tool/oem signs {gsl.bin + reg_info.bin + u-boot} -> boot_image.bin.
#
# CI uses the generic apt cross toolchain (aarch64-linux-gnu-). On a host with a
# too-new GCC (>=15 defaults to C23 and breaks u-boot 2022.07) override with the
# vendor toolchain, e.g.:  CROSS_COMPILE=aarch64-v01c01-linux-musl- bash build.sh

export ARCH="arm"
export CROSS_COMPILE="${CROSS_COMPILE:-aarch64-linux-gnu-}"
export CHIP="hi3519dv500"
HIGZIP_DST="arch/arm/cpu/armv8/${CHIP}/hw_compressed"
PYTHON="${PYTHON:-python3}"

# binning -> DDR register table (reginfo/<name>.bin from RegBin)
declare -A reginfo
reginfo[dmeb]="Hi3519DV500-DMEB_6L_T_DDR4_2666M-2GB_16bitx2-A55_1G.bin"
reginfo[dmebpro]="Hi3519DV500-DMEBPRO_4L_flyby_DDR4_2666M-2GB_16bitx2-A55_1G.bin"

BUILD_DIR="output"
mkdir -p ${BUILD_DIR}

build_higzip(){
    # hi-gzip: gzip-1.11 with an 8 KiB window (hi_gzip.patch) used to compress u-boot.
    if [ ! -f ${HIGZIP_DST}/gzip ]; then
        make -C extras/gzip
        cp -f extras/gzip/bin/gzip ${HIGZIP_DST}/gzip
        chmod +x ${HIGZIP_DST}/gzip
    fi
}

build_gsl(){
    # GSL = first-stage loader the boot ROM verifies/loads; signed into every image.
    # Must build from inside gsl/: its Makefile uses $(PWD) for -I include paths, so
    # `make -C gsl` would resolve them against the repo root and fail (otp.c: types.h).
    ( cd gsl && make CHIP=${CHIP} )
    cp -f gsl/pub/gsl.bin image_tool/input/gsl.bin
}

build_dv500(){
    for BINNING in dmeb dmebpro; do
        echo "==== ${CHIP} ${BINNING} : ${reginfo[$BINNING]} ===="
        make distclean
        build_higzip
        make ${CHIP}_openipc_defconfig
        make -j"$(nproc)"
        make u-boot-z.bin
        make u-boot-z.clean

        # raw u-boot-z (pre-signing) — boots from NOR for the (future) QEMU smoke gate;
        # identical across binnings, so one copy suffices.
        cp -f u-boot-${CHIP}.bin ${BUILD_DIR}/smoke-${CHIP}.bin

        # sign with image_tool: gsl + DDR reg table + u-boot -> boot_image.bin
        cp -f u-boot-${CHIP}.bin image_tool/input/u-boot-original.bin
        cp -f reginfo/${reginfo[$BINNING]} image_tool/input/reg_info.bin
        ( cd image_tool && ${PYTHON} oem/oem_quick_build.py )
        # the signer logs errors but still exits 0 — verify the image really exists
        test -f image_tool/image/oem/boot_image.bin
        mv image_tool/image/oem/boot_image.bin ${BUILD_DIR}/boot-${CHIP}-${BINNING}-nor.bin
        echo "  -> ${BUILD_DIR}/boot-${CHIP}-${BINNING}-nor.bin"
    done
}

build_gsl
build_dv500

echo "=== artifacts ==="
ls -la ${BUILD_DIR}/
