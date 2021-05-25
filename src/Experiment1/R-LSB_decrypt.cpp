//
// Created by Frank's Laptop on 2021/5/25.
//

#include <cstdio>

#include "LBitmap1.h"

int main(int argc, char **argv) {
    ln::LBitmap1 image;
    image.ReadBmp("sky-modified.bmp");

    FILE *fp = fopen("result.exe", "wb");

    fseek(fp, 0, 0);
    unsigned char tc = 0, cnt = 0;

    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p = image.Pixel(x, y);
            tc |= ((p[0] & (unsigned char) 1) << (cnt++));

            if (cnt == 8) {
                fwrite(&tc, 1, 1, fp);
                cnt = tc = 0;
            }
        }
    }
    fclose(fp);
    return 0;
}

