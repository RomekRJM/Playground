#include "stdio.h"

unsigned char tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
unsigned int tmpWord1, tmpWord2, tmpWord3, tmpWord4;

char file[] = "hash.txt";

void fast_16b_hash() {

    tmp5 = 0 ^ tmp1; // lsb
    tmp6 = 0 ^ tmp2; // msb

    tmpWord1 = tmp5;
    tmpWord2 = (tmp6 << 8) | tmp5;

    tmp5 ^= tmp3;
    tmp6 ^= tmp4;

    tmpWord3 = tmp5;
    tmpWord4 = (tmp6 << 8) | tmp5;
}


int main(int argc, char **argv) {
    remove(file);

    FILE *fp;
    fp = fopen(file, "w");

    for (tmp1 = 0; tmp1 != 255; ++tmp1) {
        for (tmp2 = 0; tmp2 != 255; ++tmp2) {
            for (tmp3 = 0; tmp3 < 2; ++tmp3) {
                for (tmp4 = 0; tmp4 < 2; ++tmp4) {
                    fast_16b_hash();
                    fprintf(fp, "%d, %d, %d, %d: fast_16b_hash(%d, %d, %d, %d)\n", tmp1, tmp2, tmp3, tmp4,
                            tmpWord1, tmpWord2, tmpWord3, tmpWord4);
                }
            }
        }
    }

    fclose(fp);

    return 0;
}