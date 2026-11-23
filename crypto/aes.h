#pragma once
#include "main.h"
void crypt_aes_128_cbc_sha256_hmac(block key, block *blocks, int num_blocks, block iv);