//
// Created by Frank's Laptop on 2021/5/25.
//

#include <cstdio>

#include "LBitmap1.h"

int main(int argc, char **argv) {
    ln::LBitmap1 image;
    image.ReadBmp("sky-s.bmp");

    FILE *fp = fopen("test.exe", "rb");
    fseek(fp, 0, 0);
    unsigned char tc, cnt = 0;
    fread(&tc, 1, 1, fp);
    bool eofFlag = false;

    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p = image.Pixel(x, y);
            if (!eofFlag && (tc & ((unsigned char) ((unsigned char) 1 << (cnt++)))))
                p[0] |= (unsigned char) 0b00000001;
            else p[0] &= (unsigned char) 0b11111110;

            if (cnt == 8) {
                cnt = 0;
                if (fread(&tc, 1, 1, fp) == 0)
                    eofFlag = true;
            }
        }
    }

    image.WriteBmp("sky-modified.bmp");
    fclose(fp);
    return 0;
}

