//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LSBrecorder.hpp"

int main(int argc, char **argv) {
    LSBrecorder<true, 3> recorder("sky-s.bmp", "sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image1, image2;
    image1.ReadBmp("logo.bmp");
    image2.ReadBmp("logo_r.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y), *p2 = image2.Pixel(x, y);
            recorder.writeBit(p1[0] > 128 && p1[1] > 128 && p1[2] > 128);
            recorder.writeBit(p2[0] > 128 && p2[1] > 128 && p2[2] > 128);
            recorder.writeBit(p1[0] > 128 && p1[1] > 128 && p1[2] > 128);
        }
    }
    return 0;
}

