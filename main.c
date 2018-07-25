#include "x11.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int main(void) {
    // const char *input = "";
    const char *input = "The quick brown fox jumps over the lazy dog";
    // const char *input = "DASH";
    // const char *input = "Take this kiss upon the brow! And, in parting from you now, Thus much let me avow-- You are not wrong, who deem That my days have been a dream; Yet if hope has flown away In a night, or in a day, In a vision, or in none, Is it therefore the less gone? All that we see or seem Is but a dream within a dream. I stand amid the roar Of a surf-tormented shore, And I hold within my hand Grains of the golden sand-- How few! yet how they creep Through my fingers to the deep, While I weep--while I weep! O God! can I not grasp Them with a tighter clasp? O God! can I not save One from the pitiless wave? Is all that we see or seem But a dream within a dream?";
    /*
    unsigned char input[64];
    int int32arr[] = {-1245000620, -1578223460, 654805539, -1068884769, -968029107, -8582190, 491541657, 290156804, 1046922525, 1254877013, -1307320917, 1691597203, 55068107, 1715389297, 252729336, 127805489};
    for ( int i = 0; i < (sizeof(int32arr) / sizeof(int32arr[0])); i++ ) {
        int num = int32arr[i];
        input[(i * 4) + 0] = ((unsigned int)num >> 24) & 0xff;
        input[(i * 4) + 1] = ((unsigned int)num >> 16) & 0xff;
        input[(i * 4) + 2] = ((unsigned int)num >> 8 ) & 0xff;
        input[(i * 4) + 3] = ((unsigned int)num >> 0 ) & 0xff;
    }

    printf("reading ARRAY!\n");
    for ( int i = 0; i < 16; i++ ) {
        char index = i * 4;
        int num = (input[index + 0] << 24) +
                  (input[index + 1] << 16) +
                  (input[index + 2] <<  8) +
                  (input[index + 3] <<  0) ;
        printf("num = %d\n", num);
        if ( num == int32arr[i] ) {
            printf("they match, good work!\n");
        }
        else {
            printf("NO MATCH!\n");
        }
    }
    */

    // hash and display the entire 512-bits
    int output_size = 64;
    int hexout_size = output_size + output_size + 1;

    char output[output_size];
    char hexout[hexout_size];
    hexout[hexout_size - 1] = '\0';

    x11_hash((const char *)input, output, strlen(input));
    binary_to_hex(hexout, (const char *)output, output_size);

    printf("hexout: [%s]\n", hexout);

    return 0;
}
