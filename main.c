#include "main.h"

void print_help() {
	puts("help placeholder");
}


int main(int argc, char *argv[]) {
	int opt;
	bool verbose = false;
	bool user_key = false;
	uint8_t	aes_keyl[16];
	while((opt = getopt(argc, argv, "vk:h")) != -1) {
		switch (opt) {
			case 'v':
				verbose = true;
				break;
			case 'k':
				user_key = true;
				char *ptr = optarg;
				for (int i = 0; i < 16; i++) {
					uint8_t temp_val;
					int chars_read = 0;

					if (sscanf(ptr, "%hhx%n", &temp_val, &chars_read) != 1) {
						fprintf(stderr, "Error: -k requires 16 valid hex bytes.\n");
						return 0;
					}

					aes_keyl[i] = temp_val;
					ptr += chars_read;
				}
				break;
			case 'h':
				print_help();
				return 1;
			default:
				print_help();
				return 1;
		}
	}
	//attempt to add error handeling for improper arg usage and h arg.
	// add else wraper to AES key gen if one is supplyed
	// add verbose arg just in case they want the blocks to be printed instead of just a file
	// add file support
	//generates an AES key from kernel entropy pool if no key is supplyed
	if (user_key == false) {
		if (getentropy(aes_keyl, sizeof(aes_keyl)) != 0) {
			perror("getentropy failed");
			return 1;
		}
		if(verbose==true) {
			printf("AES key: ");
			for(int i = 0; i < 16; i++) {
				printf("%02X ", aes_keyl[i]);
			}
			fflush(stdout);
			putchar('\n');
		}
	}

	block aes_key;
	for (int x = 0; x < 16; x++) {
		aes_key.data[x%4][x/4] = aes_keyl[x];
	}
	if(verbose==true) {
	    printf("\n--- AES KEY ---\n");
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                printf("%02X ", (unsigned char)aes_key.data[r][c]);
            }
            printf("\n");
        }

	}
	// grabs text from input
	char *text = NULL;
	ssize_t string_length = 0;

	// checks for piped data
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

	// to be complient with PKCS#7
	int padding = 16 - (string_length % 16);
	int num_blocks = (string_length/16)+1;
	block *blocks = malloc(num_blocks * sizeof(block));
	for (int i = 0; i < num_blocks; i++) {
		for (int x = 0; x < 16; x++) {
			if ((i*16)+x < string_length) {
				blocks[i].data[x%4][x/4] = text[(i*16)+x];
			} else {
				blocks[i].data[x%4][x/4] = padding;
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
