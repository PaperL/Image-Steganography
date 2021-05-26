//
// Created by Libro on 2021/5/25.
//

#include "LSBrecorderEx.hpp"

int main(int argc, char **argv) {
    LSBrecorderEx<true, 3> recorder("sky-s.bmp", "sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image1;
    image1.ReadBmp("city.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y);
            for (int i = 0; i < 8; ++i)
                recorder.writeBit(p1[0] & ((unsigned char)1<<i));
        }
    }
    return 0;
}

