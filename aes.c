#include "main.h"

static const uint8_t mix_columns_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};
static const uint8_t inverse_mix_columns_matrix[4][4] = {
    {0x0D, 0x0A, 0x0C, 0x09},
    {0x09, 0x0D, 0x0A, 0x0C},
    {0x0C, 0x09, 0x0D, 0x0A},
    {0x0A, 0x0C, 0x09, 0x0D}
};
static const uint8_t round_constants[10][4] = {
    {0x01,0x00,0x00,0x00},
    {0x02,0x00,0x00,0x00},
    {0x04,0x00,0x00,0x00},
    {0x08,0x00,0x00,0x00},
    {0x10,0x00,0x00,0x00},
    {0x20,0x00,0x00,0x00},
    {0x40,0x00,0x00,0x00},
    {0x80,0x00,0x00,0x00},
    {0x1b,0x00,0x00,0x00},
    {0x36,0x00,0x00,0x00},
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
static uint8_t sbox() {
return 1;
}
void sub_bytes() {
    

}
void shift_rows(block *blocks,int num_blocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int r = 0; r < 4; r++) {
            uint8_t temp[4];
            for(int c = 0; c < 4; c++) {
                temp[c] = blocks[i].data[c][(c+c)%4];
            }
            for(int c = 0; c < 4; c++) {
                blocks[i].data[r][c] = temp[c];
            }
        }
    }
}
void mix_columns(block *blocks,int num_blocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int c = 0; c < 4; c++) {
            uint8_t tempcol[4];
            for(int r = 0; r < 4; r++) {
                tempcol[r] = gmol(mix_columns_matrix[r][0], blocks[i].data[0][c]) ^
                             gmol(mix_columns_matrix[r][1], blocks[i].data[1][c]) ^
                             gmol(mix_columns_matrix[r][2], blocks[i].data[2][c]) ^
                             gmol(mix_columns_matrix[r][3], blocks[i].data[3][c]);
            }            
            for(int r = 0; r < 4; r++) {
                blocks[i].data[r][c] = tempcol[r];
            }
        }
    }
}

void inverse_mix_columns(block *blocks,int num_blocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int c = 0; c < 4; c++) {
            uint8_t tempcol[4];
            for(int r = 0; r < 4; r++) {
                tempcol[r] = gmol(inverse_mix_columns_matrix[r][0], blocks[i].data[0][c]) ^
                             gmol(inverse_mix_columns_matrix[r][1], blocks[i].data[1][c]) ^
                             gmol(inverse_mix_columns_matrix[r][2], blocks[i].data[2][c]) ^
                             gmol(inverse_mix_columns_matrix[r][3], blocks[i].data[3][c]);
            }
            for(int r = 0; r < 4; r++){
                blocks[i].data[r][c] = tempcol[r];
            }
        }
    }
}
static void key_expansion(block *keys) {
    for(int i = 0; i < 11; i++) {
        for(int c = 0; c < 4; c++) {
            for(int r = 0; r < 4; r++) {
                printf("%02X ", keys[i].data[r][c]);
            }
        }
    }
}
void add_round_key(block *blocks,int num_blocks, block key) {  
    block keys[11];
    keys[0] = key;
    for(int i = 0; i < 11; i++) {
        for(int c = 0; c < 4; c++) {
            for(int r = 0; r < 4; r++) {
                getrandom(&keys[i].data[r][c], 1, 0);
            }
        }
    }
    for(int i = 0; i < 11; i++) {
        for(int c = 0; c < 4; c++) {
            for(int r = 0; r < 4; r++) {
                printf("%02X ", keys[i].data[r][c]);
            }
        }
    key_expansion(keys);
    }

}
