SECURITY_SUBSYS_DIR := $(srctree)/product/security_subsys

include $(SECURITY_SUBSYS_DIR)/km/build.mak
include $(SECURITY_SUBSYS_DIR)/otp/build.mak
include $(SECURITY_SUBSYS_DIR)/cipher/build.mak
include $(SECURITY_SUBSYS_DIR)/crypto_osal/build.mak
include $(SECURITY_SUBSYS_DIR)/init/build.mak

ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/security_subsys_common/include/common_include
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/security_subsys_common/include/hal_include
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/security_subsys_common/include/drv_include
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/security_subsys_common/ot_mpi_api
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/security_subsys_common/drv_code
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/crypto_osal
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/ext_inc
ccflags-y 	+= -I${SECURITY_SUBSYS_DIR}/init

ccflags-y	+= -DCONFIG_CRYPTO_CHIP_HI3519DV500
ccflags-y	+= -DCRYPTO_CTR_NON_ALIGN_SUPPORT
ccflags-y	+= -DCRYPTO_SYMC_ADDR_NOT_ALIGN_SUPPORT
