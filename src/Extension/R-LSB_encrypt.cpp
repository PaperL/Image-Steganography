//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LSBrecorder.hpp"

int main(int argc, char **argv) {
    LSBrecorder recorder("sky-s.bmp", "sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image2;
    image2.ReadBmp("logo.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p2 = image2.Pixel(x, y);
            recorder.writeBit(p2[0] > 128 && p2[1] > 128 && p2[2] > 128);
        }
    }
    return 0;
}

