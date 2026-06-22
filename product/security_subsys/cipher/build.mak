# HAL
obj-y	+= security_subsys_common/hal_code/pke_v4/hal_pke.o
obj-y	+= security_subsys_common/hal_code/spacc_v4/hal_hash.o
obj-y	+= security_subsys_common/hal_code/spacc_v4/hal_symc.o
obj-y	+= security_subsys_common/hal_code/trng_v4/hal_trng.o

# DRV
obj-y	+= security_subsys_common/drv_code/crypto_drv_common.o
obj-y	+= security_subsys_common/drv_code/drv_hash.o
obj-y	+= security_subsys_common/drv_code/drv_pbkdf2_hard.o
obj-y	+= security_subsys_common/drv_code/drv_pke_ecc_curve.o
obj-y	+= security_subsys_common/drv_code/drv_pke_ecc.o
obj-y	+= security_subsys_common/drv_code/drv_pke_rsa.o
obj-y	+= security_subsys_common/drv_code/drv_pke.o
obj-y	+= security_subsys_common/drv_code/drv_symc_mac_hard.o
obj-y	+= security_subsys_common/drv_code/drv_symc.o
obj-y	+= security_subsys_common/drv_code/drv_trng.o

# MPI
obj-y	+= cipher/ot_mpi_hash.o
obj-y	+= cipher/ot_mpi_kdf.o
obj-y	+= cipher/ot_mpi_pke.o
obj-y	+= cipher/ot_mpi_symc.o
obj-y	+= cipher/ot_mpi_trng.o