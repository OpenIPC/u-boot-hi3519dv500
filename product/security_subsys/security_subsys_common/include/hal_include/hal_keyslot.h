/*
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 */

#ifndef HAL_KEYSLOT_H
#define HAL_KEYSLOT_H

#include "crypto_type.h"
#include "crypto_km_struct.h"

td_s32 hal_keyslot_lock(td_u32 keyslot_num, crypto_keyslot_type keyslot_type);

td_s32 hal_keyslot_unlock(td_u32 keyslot_num, crypto_keyslot_type keyslot_type);

#endif