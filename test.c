#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    uint8_t data[4][4];
} block;

int main() {
	char *text = NULL;
	ssize_t string_length = 0;
	if (isatty(STDIN_FILENO)) {
		printf("enter your string: ");
		fflush(stdout);
		size_t buf_size = 0;
		string_length = getline(&text, &buf_size, stdin);
		if (string_length == -1) {
			perror("getline failed");
			return 1;
		}
	//rewrite
	} else {
		size_t capacity = 4096;
		text = malloc(capacity);
		if (!text) {
			perror("malloc failed");
			return 1;
		}

		size_t total_read = 0;
		size_t n = 0;
		while (1) {
            if (total_read + 1 >= capacity) {
                capacity *= 2;
                char *new_text = realloc(text, capacity);
                if (!new_text) {
                    perror("realloc failed");
                    free(text);
                    return 1;
                }
                text = new_text;
            }

            n = fread(text + total_read, 1, capacity - total_read - 1, stdin);
            if (n == 0) {
                break; 
            }
            total_read += n;
        }
		text[total_read] = '\0';
		string_length = total_read;
	}
	int padding = 16 - (string_length % 16);
	// to comply with PKCS#7
	int num_blocks = (string_length/16)+1;
	block *blocks = malloc(num_blocks * sizeof(block));
	for (int i = 0; i < num_blocks; i++) {
		for (int x = 0; x < 16; x++) {
			if ((i*16)+x < string_length) {
				blocks[i].data[x/4][x%4] = text[(i*16)+x];
			} else {
				blocks[i].data[x/4][x%4] = padding;
			}
		}
	}
	//rewrite
	for (int i = 0; i < num_blocks; i++) {
        printf("\n--- Block %d ---\n", i);
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                // Print each byte as a 2-digit uppercase hex value
                printf("%02X ", (unsigned char)blocks[i].data[r][c]);
            }
            printf("\n");
        }
    }
fflush(stdout);
free(blocks);
free(text);

return 0;
}
