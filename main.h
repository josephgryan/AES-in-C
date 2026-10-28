#pragma once
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct block {
    uint8_t data[4][4];
} block;

