#include "x11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "util.h"

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [OPTIONS] [hex_string]\n", prog_name);
    fprintf(stderr, "  hex_string: Input data as hexadecimal string (e.g., 48656c6c6f)\n");
    fprintf(stderr, "              If omitted, reads from stdin\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -l, --long  Output full 512-bit hash (default: 256-bit)\n");
    fprintf(stderr, "\nExamples:\n");
    fprintf(stderr, "  %s 4461736820697320636f6f6c\n", prog_name);
    fprintf(stderr, "  %s -l 4461736820697320636f6f6c\n", prog_name);
    fprintf(stderr, "  echo -n \"00\" | %s\n", prog_name);
    fprintf(stderr, "  echo -n \"00\" | %s --long\n", prog_name);
}

int is_valid_hex(const char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (!isxdigit(str[i]) && str[i] != '\n' && str[i] != '\r') {
            return 0;
        }
    }
    return 1;
}

char* read_stdin(size_t *out_len) {
    size_t capacity = 1024;
    size_t len = 0;
    char *buffer = malloc(capacity);

    if (!buffer) {
        return NULL;
    }

    int c;
    while ((c = getchar()) != EOF) {
        // Skip newlines and carriage returns
        if (c == '\n' || c == '\r') {
            continue;
        }

        if (len >= capacity - 1) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }

        buffer[len++] = c;
    }

    buffer[len] = '\0';
    *out_len = len;
    return buffer;
}

int process_hex(const char *hex_input, size_t hex_len, int use_long_output) {
    // Validate hex string
    if (hex_len == 0) {
        fprintf(stderr, "Error: Empty hex string\n");
        return 1;
    }

    if (hex_len % 2 != 0) {
        fprintf(stderr, "Error: Hex string must have even number of characters\n");
        return 1;
    }

    if (!is_valid_hex(hex_input, hex_len)) {
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
    int full_output_size = 64;  // 512 bits = 64 bytes
    int output_size = use_long_output ? full_output_size : 32;  // 256 bits = 32 bytes by default
    int hexout_size = output_size * 2 + 1;

    char output[full_output_size];
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

int main(int argc, char *argv[]) {
    int use_long_output = 0;
    int arg_idx = 1;

    // Parse options
    if (argc > 1 && (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--long") == 0)) {
        use_long_output = 1;
        arg_idx = 2;
    }

    if (argc > 3 || (argc == 3 && !use_long_output)) {
        print_usage(argv[0]);
        return 1;
    }

    if (argc >= 2 && arg_idx < argc) {
        // Process command-line argument
        const char *hex_input = argv[arg_idx];
        return process_hex(hex_input, strlen(hex_input), use_long_output);
    } else {
        // Read from stdin
        size_t hex_len;
        char *hex_input = read_stdin(&hex_len);

        if (!hex_input) {
            fprintf(stderr, "Error: Failed to read from stdin\n");
            return 1;
        }

        int result = process_hex(hex_input, hex_len, use_long_output);
        free(hex_input);
        return result;
    }
}
