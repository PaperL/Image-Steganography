//
// Created by Libro on 2021/5/25.
//

#include "LSBrecorderEx.hpp"

int main(int argc, char **argv) {
    LSBrecorderEx<false, 3> recorder("sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image1;
    image1.ReadBmp("sky-modified.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y);
            p1[0] = 0;
            for (int i = 0; i < 8; ++i)
                p1[0] ^= ((unsigned char) recorder.getBit()) << i;
            p1[2] = p1[1] = p1[0];
        }
    }
    image1.WriteBmp("decrypt_city.bmp");
    return 0;
}

