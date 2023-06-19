#include "stdio.h"

unsigned char tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
unsigned int hash1msb, hash1lsb, hash2msb, hash2lsb, hash3msb, hash3lsb, hash4msb, hash4lsb;

char file[] = "hash.txt";

void fast_16b_hash() {

    hash1lsb = 0 ^ tmp1; // lsb
    hash1msb = 0; // msb

    hash2lsb = hash1lsb;
    hash2msb = 0 ^ tmp2;

    hash3lsb = hash2lsb ^ tmp3;
    hash3msb = hash2msb;

    hash4lsb = hash3lsb;
    hash4msb = hash3msb ^ tmp4;
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
                    fprintf(fp, "%d, %d, %d, %d: fast_16b_hash(%d, %d, %d, %d, %d, %d, %d, %d)\n",
                            tmp1, tmp2, tmp3, tmp4, hash1lsb, hash1msb, hash2lsb, hash2msb, hash3lsb, hash3msb, hash4lsb, hash4msb);
                }
            }
        }
    }

    fclose(fp);

    return 0;
}