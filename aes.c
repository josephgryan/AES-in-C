#include "main.h"

static const uint8_t mix_columns_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};
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
    for(int i = 0; i < 4; i++) {
        for(int c = 0; c < 4; c++) {
            uint8_t temp[4];
            for(int r = 0; r < 4; r++) {
                temp[r] = block[i].data[r][c]
            }
            for(int r = 0; r < 4; r++) {
                blocks[i].data[r][c] = temp[r]
            }
        }
        
    }

}
void add_round_key() {

}
static uint8_t gmol(int a, int byte) {
    int times = a/2
    bool xor = (a%2 == 1)
}
// possibly remove
static uint8_t xtime(int byte, int times) {
    uint8_t nbyte;
    for(int i = 0; i < times; i++) {
        if (byte & 0x80) {
            nbyte = (byte << 1) ^ 0x1B;
        }
        else {
            nbyte = byte << 1;
        }
        byte = nbyte;
    }
    return nbyte;
}