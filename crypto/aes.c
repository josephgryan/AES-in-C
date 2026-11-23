#include "../main.h"
#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
// remove after implimenting sha-256
#include <openssl/evp.h>
#include <openssl/params.h>
#include <stddef.h>
#include <stdint.h>
static const uint8_t mix_columns_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};
static const uint8_t inverse_mix_columns_matrix[4][4] = {
    {0x0E, 0x0B, 0x0D, 0x09},
    {0x09, 0x0E, 0x0B, 0x0D},
    {0x0D, 0x09, 0x0E, 0x0B},
    {0x0B, 0x0D, 0x09, 0x0E}
};
static const uint32_t round_constants[11] = {
    0x00000000,
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000,
    0x1b000000,
    0x36000000
};
static const uint8_t sbox_matrix [16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};
static uint8_t gmol(uint8_t a, uint8_t byte) {
    uint8_t newbyte = 0;
    for(int i = 0; i < 8; i++) {
        if(0 != (byte & 1)) {
            newbyte ^= a;
        }
        bool high_bit = (a & 0x80);
            a = (a << 1);
        if(high_bit) {
            a = 0x1B ^ a;
        }
        byte = byte >> 1;
    }
    return newbyte;
}
static uint8_t sbox(uint8_t a) {
    return sbox_matrix[a >> 4][a & 0x0F];
}
block sub_bytes(block block) {
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            block.data[r][c] = sbox(block.data[r][c]);
        }
    }
    return block;
}
block shift_rows(block block) {
    for(int r = 1; r < 4; r++) {
        uint8_t temp[4];
        for(int c = 0; c < 4; c++) {
            temp[c] = block.data[r][(c + r) % 4];
        }
        for(int c = 0; c < 4; c++) {
            block.data[r][c] = temp[c];
        }
    }
    return block;
}
block mix_columns(block block) {
    for(int c = 0; c < 4; c++) {
        uint8_t tempcol[4];
        for(int r = 0; r < 4; r++) {
            tempcol[r] = gmol(mix_columns_matrix[r][0], block.data[0][c]) ^
                            gmol(mix_columns_matrix[r][1], block.data[1][c]) ^
                            gmol(mix_columns_matrix[r][2], block.data[2][c]) ^
                            gmol(mix_columns_matrix[r][3], block.data[3][c]);
        }            
        for(int r = 0; r < 4; r++) {
            block.data[r][c] = tempcol[r];
        }
    }
    return block;
}

block inverse_mix_columns(block block) {
    for(int c = 0; c < 4; c++) {
        uint8_t tempcol[4];
        for(int r = 0; r < 4; r++) {
            tempcol[r] =    gmol(inverse_mix_columns_matrix[r][0], block.data[0][c]) ^
                            gmol(inverse_mix_columns_matrix[r][1], block.data[1][c]) ^
                            gmol(inverse_mix_columns_matrix[r][2], block.data[2][c]) ^
                            gmol(inverse_mix_columns_matrix[r][3], block.data[3][c]);
        }
        for(int r = 0; r < 4; r++){
            block.data[r][c] = tempcol[r];
        }
    }
    return block;
}

static uint32_t sub_word(uint32_t word) {
    uint8_t b0 = sbox((word >> 24) & 0xFF);
    uint8_t b1 = sbox((word >> 16) & 0xFF);
    uint8_t b2 = sbox((word >> 8)  & 0xFF);
    uint8_t b3 = sbox((word >> 0)  & 0xFF);
    
    return ((uint32_t)b0 << 24) | 
           ((uint32_t)b1 << 16) | 
           ((uint32_t)b2 << 8)  | 
            (uint32_t)b3;
}
static uint32_t rot_word(uint32_t word) {
    return((word << 8) | (word >> 24));
}

void key_expansion(block *keys) {
    uint32_t words[44];
    for (int c = 0; c < 4; c++) {
        words[c] = ((uint32_t)keys[0].data[0][c] << 24) |
                   ((uint32_t)keys[0].data[1][c] << 16) |
                   ((uint32_t)keys[0].data[2][c] << 8)  |
                   ((uint32_t)keys[0].data[3][c]);
    }
    for(int i = 4; i < 44; i++) {
        uint32_t temp = words[i-1];
        if(i%4==0){
            temp = sub_word(rot_word(temp))^round_constants[i/4];
        }
        words[i]=words[i-4]^temp;
    }
    for (int round = 0; round < 11; round++) {
        for (int c = 0; c < 4; c++) {
            uint32_t w = words[round * 4 + c];
            keys[round].data[0][c] = (w >> 24) & 0xFF;
            keys[round].data[1][c] = (w >> 16) & 0xFF;
            keys[round].data[2][c] = (w >> 8)  & 0xFF;
            keys[round].data[3][c] = (w >> 0)  & 0xFF;
        }
    }
    
}
block add_round_key(block *keys, block block, int round) {
    for (int c = 0; c < 4; c++) {
        uint32_t state = 0, key = 0;

        for (int r = 0; r < 4; r++) {
            state = (state << 8) | block.data[r][c];
            key   = (key << 8)   | keys[round].data[r][c];
        }

        state ^= key;

        for (int r = 3; r >= 0; r--) {
            block.data[r][c] = state & 0xFF;
            state >>= 8;
        }
    }
    return block;
}
block crypt_aes_128(block *keys, block block) {
    add_round_key(keys, block, 0);
    for(int i = 1; i < 10; i++) {
        block = sub_bytes(block);
        shift_rows(block);
        mix_columns(block);
        add_round_key(keys, block, i);
    }
    
    sub_bytes(block);
    shift_rows(block);
    add_round_key(keys, block, 10);
    return block;
}
block xorblocks(block blocka, block blockb) {
    block blockc;
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++){
            blockc.data[r][c] = blocka.data[r][c] ^ blockb.data[r][c];
        }
    }
    return blockc;
}
block hmac_sha256(block *blocks,int num_blocks, uint8_t *hmac_key) {
    block *tempblocks = malloc(sizeof(block)*(num_blocks+1));
    memcpy(tempblocks, blocks,(num_blocks+1)*sizeof(block));
    uint8_t sha256hash[32] = {0};
    size_t out_len = 0;
    EVP_Q_digest(NULL, "SHA256", NULL, tempblocks, (1+num_blocks)*sizeof(block), sha256hash, &out_len) && out_len == 32;
    block hash;
    free(tempblocks);
    return hash;
}
void crypt_aes_128_cbc_sha256_hmac(block key, block *blocks, int num_blocks, block iv, uint8_t *hmac_user_key) {
    block keys[11];
    keys[0] = key;
    key_expansion(keys);
    blocks[0] = crypt_aes_128(keys, xorblocks(blocks[0] , iv));
    for(int i = 1; i < num_blocks; i++) {
        blocks[i] = crypt_aes_128(keys, xorblocks(blocks[i-1], blocks[i]));
    }
    void *tmpptr = realloc(blocks, (num_blocks+2)*sizeof(block));
    if(tmpptr == NULL){
        perror("realloc failed in crypt_aes_128_cbc_sha256_hmac, cant continue with normal function");
        exit(1);
    } else {
        blocks = tmpptr;
    }
    memmove((uint8_t *)blocks + sizeof(block), blocks, num_blocks * sizeof(block));
    blocks[0] = iv;
    blocks[num_blocks+2] = hmac_sha256(blocks, num_blocks,hmac_user_key);
}   