//
// Created by Frank's Laptop on 2021/5/25.
//

#include "LSBrecorder.hpp"

int main(int argc, char **argv) {
    LSBrecorder<false, 3> recorder("sky-modified.bmp", 1024, 768);
    ln::LBitmap1 image1, image2, image3;
    image1.ReadBmp("sky-modified.bmp");
    image2.ReadBmp("sky-modified.bmp");
    image3.ReadBmp("sky-modified.bmp");
    for (size_t y = 0; y < 768; ++y) {
        for (size_t x = 0; x < 1024; ++x) {
            unsigned char *p1 = image1.Pixel(x, y), *p2 = image2.Pixel(x, y), *p3 = image3.Pixel(x, y);
            if (recorder.getBit())
                p1[0] = p1[1] = p1[2] = 255;
            else p1[0] = p1[1] = p1[2] = 0;
            if (recorder.getBit())
                p2[0] = p2[1] = p2[2] = 255;
            else p2[0] = p2[1] = p2[2] = 0;
            if (recorder.getBit())
                p3[0] = p3[1] = p3[2] = 255;
            else p3[0] = p3[1] = p3[2] = 0;
        }
    }
    image1.WriteBmp("decrypt1.bmp");
    image2.WriteBmp("decrypt2.bmp");
    image3.WriteBmp("decrypt3.bmp");
    return 0;
}

