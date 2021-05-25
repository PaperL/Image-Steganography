//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LBitmap1.h"

int main(int argc, char **argv) {
    ln::LBitmap1 image1, image2;
    image1.ReadBmp("sky-s.bmp");
    image2.ReadBmp("logo.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y), *p2 = image2.Pixel(x, y);
            if (p2[0] > 128 && p2[1] > 128 && p2[2] > 128)
                p1[0] |= (unsigned char) 0b00000001;
            else p1[0] &= (unsigned char) 0b11111110;
        }
    }
    image1.WriteBmp("sky-modified.bmp");
    return 0;
}

