#include "main.h"

void sub_bytes() {
    

}
void shift_rows(Block *blocks,int numblocks) {
    for(int i = 0; i < num_blocks; i++) {
        for(int r = 0; r < 3; r++) {
            for(int c = 0; c < 3; c++;) {
                blocks[i].data[r][c] = (blocks[i].data[r][c]+r)%3;
            }
        }
    }
}
void mix_columns() {

}
void add_round_key() {

}