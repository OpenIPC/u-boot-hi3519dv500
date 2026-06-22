/*
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 */

#ifndef HAL_TRNG_H
#define HAL_TRNG_H

#include "crypto_type.h"

td_s32 hal_cipher_trng_init(td_void);

td_s32 hal_cipher_trng_get_random(td_u32 *randnum);

td_s32 hal_cipher_trng_deinit(td_void);

#endif