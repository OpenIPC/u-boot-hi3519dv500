/*
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 */

#include <common.h>
#include "crypto_osal_adapt.h"
#include "crypto_drv_common.h"
#include "drv_trng.h"

td_s32 crypto_get_random(td_u32 *randnum)
{
    return drv_cipher_trng_get_random(randnum);
}

#define OTP_BASE_ADDR 0x101E0000
#define OTP_REG_SIZE 0x100
#define OTP_SM2_BIT_OFFSET 25
#define OTP_SM3_BIT_OFFSET 26
#define OTP_SM4_BIT_OFFSET 27

td_bool crypto_sm_support(crypto_sm_alg alg)
{
    td_u32 value = 0;
    td_u32 sm_offset = 0;
    td_u32 bit_offset = 0;

    value = otpc_reg_read(sm_offset);

    if (alg == CRYPTO_SM_ALG_SM2) {
        bit_offset = OTP_SM2_BIT_OFFSET;
    } else if (alg == CRYPTO_SM_ALG_SM3) {
        bit_offset = OTP_SM3_BIT_OFFSET;
    } else if (alg == CRYPTO_SM_ALG_SM4) {
        bit_offset = OTP_SM4_BIT_OFFSET;
    } else {
        return TD_FALSE;
    }

    if (value & (1 << bit_offset)) {
        return TD_FALSE;
    }
    return TD_TRUE;
}

void crypto_cache_flush(uintptr_t base_addr, td_u32 size)
{
    flush_cache(base_addr, size);
}

void crypto_dcache_enable(void)
{
    dcache_enable();
}

void crypto_dcache_disable(void)
{
    dcache_disable();
}

#define CPU_ID_STAT                     (0x0018)
#define CRYPTO_CPU_ID_SCPU              (0xa5)
#define CRYPTO_CPU_ID_ACPU              (0xaa)

crypto_cpu_type crypto_get_cpu_type(td_void)
{
    td_u32 cpu_id = ca_misc_reg_read(CPU_ID_STAT) & 0x00ff;
    if (cpu_id == CRYPTO_CPU_ID_SCPU) {
        return CRYPTO_CPU_TYPE_SCPU;
    } else if (cpu_id == CRYPTO_CPU_ID_ACPU) {
        return CRYPTO_CPU_TYPE_ACPU;
    }
    return CRYPTO_CPU_TYPE_INVALID;
}