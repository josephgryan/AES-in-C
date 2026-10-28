#pragma once
#include "main.h"
void shift_rows(block *blocks,int num_blocks);
void add_round_key();
void mix_columns();
void sub_bytes();