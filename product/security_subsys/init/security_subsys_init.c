/*
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 */

#include "security_subsys_init.h"
#include "drv_common.h"
#include "crypto_drv_common.h"
#include "drv_pke.h"
#include "drv_hash.h"
#include "drv_symc.h"
#include "drv_trng.h"
#include "drv_klad.h"
#include "drv_keyslot.h"

#include <common.h>
#include <malloc.h>


static td_void *uboot_malloc_coherent(td_u32 size, crypto_mem_type mem_type, const td_char *buffer_name)
{
    (void)buffer_name;
    (void)mem_type;
    return malloc(size);
}

static td_phys_addr_t uboot_get_phys_addr(td_void *ptr)
{
    return (td_phys_addr_t)(ptr);
}

int crypto_cipher_init(td_void)
{
    crypto_drv_func func_list = {
        .malloc_coherent = uboot_malloc_coherent,
        .free_coherent  = free,
        .get_phys_addr = uboot_get_phys_addr,
    };
    drv_cipher_register_func(&func_list);
    dcache_disable();
    drv_cipher_pke_init();
    drv_cipher_trng_init();
    drv_cipher_hash_init();
    drv_cipher_symc_init();
    drv_keyslot_init();
    return 0;
}

int crypto_cipher_deinit(td_void)
{
    dcache_enable();
    drv_cipher_pke_deinit();
    drv_cipher_trng_deinit();
    drv_cipher_hash_deinit();
    drv_cipher_symc_deinit();
    drv_keyslot_deinit();
    return 0;
}