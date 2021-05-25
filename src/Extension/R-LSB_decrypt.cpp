//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LSBrecorder.hpp"

int main(int argc, char **argv) {
    LSBrecorder<false> recorder("sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image;
    image.ReadBmp("sky-modified.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p = image.Pixel(x, y);
            if (recorder.getBit())
                p[0] = p[1] = p[2] = 255;
            else p[0] = p[1] = p[2] = 0;
        }
    }
    image.WriteBmp("decrypt.bmp");
    return 0;
}

