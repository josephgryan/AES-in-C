#include "main.h"

void sub_bytes() {
    

}
void shift_rows(block *blocks,int num_blocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int r = 0; r < 4; r++) {
            uint8_t temp[4];
            for(int c = 0; c < 4; c++) {
                temp[c] = blocks[i].data[r][(c+r)%3];
            }
            for(int c = 0; c < 4; c++) {
                blocks[i].data[r][c] = temp[c];
            }
        }
    }
}
void mix_columns() {

}
void add_round_key() {

}