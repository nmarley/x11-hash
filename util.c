#include "util.h"

void binary_to_hex(char *hex, const char *bin, unsigned int size) {
    unsigned int count;

    for (count = 0; count < size; count++) {
        sprintf(&hex[count * 2], "%02x", (unsigned char)bin[count]);
    }

    return;
}

void hex_to_binary(char * bin, const char *str, unsigned int len) {
    unsigned short count = 0;
    char num;

    while (len) {
        num = (16 * hc2int(str[0]) + hc2int(str[1]));
        str += 2;
        len -= 2;
        bin[count] = num;
        count += 1;
    }

    return;
}

char hc2int (char hc) {
    const char chrs[] = "0123456789abcdef";

    char value = -1; // sentinel
    const char *loc = strchr(chrs, hc);
    if (loc)
        value = loc - chrs;

    return value;
}

void reverse(char * dest, const char * src, unsigned int size) {
    int count = 0;
    while (size > 0) {
      dest[count] = src[(size - 1)];
      size -= 1;
      count += 1;
    }
    return;
}
