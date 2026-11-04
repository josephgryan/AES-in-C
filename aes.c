#include "main.h"

static const uint8_t mix_columns_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};

static uint8_t gmol(uint8_t a, uint8_t byte) {
    uint8_t newbyte = 0;
    for(int i = 0; i < 8; i++) {
        bool high_bit = (a & 0x80);
        if(byte & 1) {
            newbyte ^= a;
        }
        a = (a << 1);
        if(high_bit) {
            a = 0x1B ^ a;
        }
        byte = byte >> 1;
    }
    return newbyte;
}
void sub_bytes() {
    

}
void shift_rows(block *blocks,int num_blocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int r = 0; r < 4; r++) {
            uint8_t temp[4];
            for(int c = 0; c < 4; c++) {
                temp[c] = blocks[i].data[r][(c+r)%4];
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
                tempcol[r] = gmol(mix_columns_matrix[0][r], blocks[i].data[r][c]) ^ gmol(mix_columns_matrix[1][r],blocks[i].data[r][c]) ^ gmol(mix_columns_matrix[2][r],blocks[i].data[r][c]) ^ gmol(mix_columns_matrix[3][r],blocks[i].data[r][c]);
            }
            for(int r = 0; r < 4; r++) {
                blocks[i].data[r][c] = tempcol[r];
            }
        }
    }
}

void add_round_key() {   

}
