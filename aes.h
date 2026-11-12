#pragma once
#include "main.h"
void shift_rows(block *blocks,int num_blocks);
void mix_columns(block *blocks,int num_blocks);
void sub_bytes();
void add_round_key(block *blocks,int num_blocks, block key);
