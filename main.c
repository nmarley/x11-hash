#include "x11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "util.h"

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <hex_string>\n", prog_name);
    fprintf(stderr, "  hex_string: Input data as hexadecimal string (e.g., 48656c6c6f)\n");
    fprintf(stderr, "\nExample:\n");
    fprintf(stderr, "  %s 4461736820697320636f6f6c\n", prog_name);
}

int is_valid_hex(const char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isxdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *hex_input = argv[1];
    size_t hex_len = strlen(hex_input);

    // Validate hex string
    if (hex_len == 0) {
        fprintf(stderr, "Error: Empty hex string\n");
        print_usage(argv[0]);
        return 1;
    }

    if (hex_len % 2 != 0) {
        fprintf(stderr, "Error: Hex string must have even number of characters\n");
        return 1;
    }

    if (!is_valid_hex(hex_input)) {
        fprintf(stderr, "Error: Invalid hex string (must contain only 0-9, a-f, A-F)\n");
        return 1;
    }

    // Convert hex string to lowercase for consistency
    char *hex_lower = malloc(hex_len + 1);
    if (!hex_lower) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    
    for (size_t i = 0; i < hex_len; i++) {
        hex_lower[i] = tolower(hex_input[i]);
    }
    hex_lower[hex_len] = '\0';

    // Calculate binary input size
    size_t binary_len = hex_len / 2;
    char *binary_input = malloc(binary_len);
    if (!binary_input) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(hex_lower);
        return 1;
    }

    // Convert hex to binary
    hex_to_binary(binary_input, hex_lower, hex_len);

    // Prepare output buffers
    int output_size = 64;  // 512 bits = 64 bytes
    int hexout_size = output_size * 2 + 1;

    char output[output_size];
    char hexout[hexout_size];
    hexout[hexout_size - 1] = '\0';

    // Compute X11 hash
    x11_hash((const char *)binary_input, output, binary_len);
    binary_to_hex(hexout, (const char *)output, output_size);

    // Print result
    printf("%s\n", hexout);

    // Cleanup
    free(hex_lower);
    free(binary_input);

    return 0;
}
