//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LBitmap1.h"

int main(int argc, char **argv) {
    ln::LBitmap1 image;
    image.ReadBmp("sky-modified.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p = image.Pixel(x, y);
            if (p[0] & (unsigned char) 1)
                p[0] = p[1] = p[2] = 255;
            else p[0] = p[1] = p[2] = 0;
        }
    }
    image.WriteBmp("decrypt.bmp");
    return 0;
}

