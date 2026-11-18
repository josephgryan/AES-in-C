#include "main.h"
#include "aes.h"

static void print_help() {
	puts("help placeholder");
}
int main(int argc, char *argv[]) {
	int opt;
	bool verbose = false;
	bool user_key = false;
	bool testing = false;
	uint8_t	aes_key[16];
	while((opt = getopt(argc, argv, "vtk:h")) != -1) {
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

					aes_key[i] = temp_val;
					ptr += chars_read;
				}
				break;
			case 'h':
				print_help();
				return 1;
			case 't':
				testing = true;
				block test_key = { .data={
					{0x2b, 0x28, 0xab, 0x09},
					{0x7e, 0xae, 0xf7, 0xcf},
					{0x15, 0xd2, 0x15, 0x4f},
					{0x16, 0xa6, 0x88, 0x3c}
				}};

				// AES-128 Plaintext: 6bc1bee22e409f96e93d7e117393172a
				block test_plaintext[1] = {{ .data={
					{0x6b, 0x2e, 0xe9, 0x73}, // Row 0
					{0xc1, 0x40, 0x3d, 0x93}, // Row 1
					{0xbe, 0x9f, 0x7e, 0x17}, // Row 2
					{0xe2, 0x96, 0x11, 0x2a}  // Row 3
				}}};
				printf("\n--- Block %d ---\n", 0);
				for (int r = 0; r < 4; r++) {
					for (int c = 0; c < 4; c++) {
						// Print each byte as a 2-digit uppercase hex value
						printf("%02X ", (unsigned char)test_plaintext[0].data[r][c]);
					}
					printf("\n");
				}
				crypt_aes_128(test_plaintext, 1, test_key);
				printf("\n--- Block %d ---\n", 0);
				for (int r = 0; r < 4; r++) {
					for (int c = 0; c < 4; c++) {
						// Print each byte as a 2-digit uppercase hex value
						printf("%02X ", (unsigned char)test_plaintext[0].data[r][c]);
					}
					printf("\n");
				}
				return 0;
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
		if (getentropy(aes_key, sizeof(aes_key)) != 0) {
			perror("getentropy failed");
			return 1;
		}
		if(verbose==true) {
			printf("AES key: ");
			for(int i = 0; i < 16; i++) {
				printf("%02X ", aes_key[i]);
			}
			fflush(stdout);
			putchar('\n');
		}
	}

	if(verbose==true) {
	    printf("\n--- AES KEY ---\n");
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                printf("%02X ", aes_key[4*r + c]);
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