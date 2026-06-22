/*
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 */

#ifndef CRYPTO_OSAL_LIB_H
#define CRYPTO_OSAL_LIB_H

#include "crypto_type.h"
#include "crypto_platform.h"

#include <common.h>
#include "linux/delay.h"
#include "securec.h"
#include "cpu_func.h"

td_s32 crypto_get_random(td_u32 *randnum);

#define crypto_udelay               udelay
#define crypto_msleep(ms)           crypto_udelay(1000 * (ms))

#define crypto_print            printf

#define crypto_ioremap_nocache(addr, size)  (td_void *)(addr)
#define crypto_iounmap(addr, size)

#define crypto_malloc(x)          (((x) > 0) ? malloc(x) : TD_NULL)
#define crypto_free(x)            {if (((x) != TD_NULL)) free(x);}

#define crypto_getpid()                         osal_get_current_pid()

#define spacc_reg_read(offset)          crypto_reg_read(SPACC_REG_BASE_ADDR + (offset))
#define spacc_reg_write(offset, value)  crypto_reg_write(SPACC_REG_BASE_ADDR + (offset), value)

#define trng_reg_read(offset)           crypto_reg_read(TRNG_REG_BASE_ADDR + (offset))
#define trng_reg_write(offset, value)   crypto_reg_write(TRNG_REG_BASE_ADDR + (offset), value)

#define pke_reg_read(offset)            crypto_reg_read(PKE_REG_BASE_ADDR + (offset))
#define pke_reg_write(offset, value)    crypto_reg_write(PKE_REG_BASE_ADDR + (offset), value)

#define km_reg_read(offset)            crypto_reg_read(KM_REG_BASE_ADDR + (offset))
#define km_reg_write(offset, value)    crypto_reg_write(KM_REG_BASE_ADDR + (offset), value)

#define otpc_reg_read(offset)              crypto_reg_read(OTPC_BASE_ADDR + (offset))
#define otpc_reg_write(offset, value)      crypto_reg_write(OTPC_BASE_ADDR + (offset), value)

#define ca_misc_reg_read(offset)            crypto_reg_read(CA_MISC_REG_BASE_ADDR + (offset))
#define ca_misc_reg_write(offset, value)    crypto_reg_write(CA_MISC_REG_BASE_ADDR + (offset), value)

#define CRYPTO_ERROR_ENV                            ERROR_ENV_NOOS

#endif