//
// Created by Libro on 2021/5/25.
//

#include "LSBrecorderEx.hpp"

int main(int argc, char **argv) {
    ln::LBitmap1 image1;
    image1.ReadBmp("sky-s.bmp");
    LSBrecorderEx<false, 3> recordEx("sky-s.bmp", 1024, 768);
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y);
            double res = recordEx.calcBitNum(x, y);
            p1[0] = p1[1] = p1[2] = (unsigned char) res * 80;
        }
    }
    std::cout << recordEx.Capacity() << '\n';
    image1.WriteBmp("gray.bmp");
    return 0;
}

