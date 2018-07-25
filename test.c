#include "x11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void get_a_record(char *, FILE *);
void extract_fields(char *, ssize_t, char *, ssize_t, char *);
void do_a_line();

int main(void) {
    char buf[255];

    char hash[65];
    char input[161];

    char bin_input[80];
    char x11_output[32];
    char rev_buffer[32];
    char hex_output[65];

    FILE *in = fopen("vectors.txt", "r");

    int test_count = 0;
    int failed = 0;
    while (!feof(in)) {
        test_count += 1;

        // get input from vectors.txt file
        get_a_record(buf, in);
        extract_fields(hash, 64 + 1, input, 160 + 1, buf);

        // convert hex input to binary
        hex_to_binary(bin_input, input, strlen(input));

        // now hash the binary input
        x11_hash(bin_input, x11_output, (strlen(input) / 2));

        // reverse the bytes
        reverse(rev_buffer, x11_output, 32);

        // convert binary hash result to hex
        binary_to_hex(hex_output, (const char *)rev_buffer, 32);

        // compare the hex result to the control
        if (0 == strncmp(hex_output, hash, 64)) {
            // good
            printf("ok %d\n", test_count);
        }
        else {
            // bad
            failed += 1;
            printf("not ok %d - x11 hash does not match test vector\n", test_count);
        }
    }
    fclose(in);

    if (!failed) {
        printf("All tests passed.\n");
        return 0;
    }

    return 1;
}

void do_a_line() {
    for (size_t i = 0; i < 72; i++) {
      printf("=");
    }
    printf("\n");
    return;
}

void get_a_record(char * buf, FILE *fp) {
    char prev;
    char curr;
    int count = 0;
    fread(&curr, 1, 1, fp);

    while (!(prev == '\n' && curr == '\n') && (!feof(fp))) {
        // move char into buffer
        buf[count] = curr;
        prev = curr;
        count += 1;

        fread(&curr, 1, 1, fp);
        //printf("curr = [%c]\n", curr);
        //printf("prev = [%c]\n", prev);
    }
    buf[count] = '\0';

    return;
}

// parse vectors.txt
void extract_fields(char *hash, ssize_t hash_size, char *input, ssize_t input_size, char *src) {
    char *ptr;

    // block # ... ignore
    ptr = strtok(src, "\n");

    // hash
    ptr = strtok(NULL, "\n");
    memcpy(hash, ptr, 64);
    hash[64] = '\0';

    // input (block header)
    ptr = strtok(NULL, "\n");
    memcpy(input, ptr, 160);
    input[160] = '\0';

    return;
}
