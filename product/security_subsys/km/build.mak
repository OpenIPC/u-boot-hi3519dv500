# MPI
obj-y	+= km/ot_mpi_km.o

# DRV
obj-y	+= security_subsys_common/drv_code/drv_keyslot.o
obj-y	+= security_subsys_common/drv_code/drv_klad.o

# HAL
obj-y	+= security_subsys_common/hal_code/km_v4/hal_keyslot.o
obj-y	+= security_subsys_common/hal_code/km_v4/hal_rkp.o
obj-y	+= security_subsys_common/hal_code/km_v4/hal_klad.o