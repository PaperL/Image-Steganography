//
// Created by Libro on 2021/5/25.
//

#ifndef IMAGE_STEGANOGRAPHY_LSBRECORDER_HPP
#define IMAGE_STEGANOGRAPHY_LSBRECORDER_HPP

#include "LBitmap1.h"
#include <string>
#include <iostream>

template<bool encrypt = true, int Channel = 1, int bitNum = 1>
class LSBrecorder {
private:
    std::string input, output;
    ln::LBitmap1 image;
    int X, Y, x, y, k, num;
public:
    LSBrecorder(const std::string &input, const std::string &output, int X, int Y) : input(input), output(output), X(X),
                                                                                     Y(Y), x(0), y(0), k(0), num(0) {
        image.ReadBmp(input.c_str());
    }

    LSBrecorder(const std::string &input, int X, int Y) : input(input), X(X),
                                                          Y(Y), x(0), y(0), k(0), num(0) {
        image.ReadBmp(input.c_str());
    }

    void writeBit(bool flag) {
        if (!encrypt) {
            std::cout << "error: not encrypt type\n";
            return;
        }
        if (y >= Y) {
            std::cout << "error: overflow\n";
            return;
        }
        unsigned char *p1 = image.Pixel(x, y);
        if (flag) p1[k] |= ((unsigned char) 0b00000001) << num;
        else p1[k] &= (unsigned char) 0b11111111 ^ ((unsigned char) 0b00000001 << num);
        ++num;
        if (num == bitNum) {
            num = 0;
            ++k;
            if (k == Channel) {
                k = 0;
                ++x;
                if (x == X) {
                    ++y;
                    x = 0;
                }
            }
        }
    }

    bool getBit() {
        if (encrypt) {
            std::cout << "error: not decrypt type\n";
            return 0;
        }
        if (y >= Y) {
            std::cout << "error: overflow\n";
            return 0;
        }
        unsigned char *p = image.Pixel(x, y);
        bool res = p[k] & ((unsigned char) (1 << num));
        ++num;
        if (num == bitNum) {
            num = 0;
            ++k;
            if (k == Channel) {
                k = 0;
                ++x;
                if (x == X) {
                    ++y;
                    x = 0;
                }
            }
        }
        return res;
    }

    ~LSBrecorder() {
        if (encrypt)
            image.WriteBmp(output.c_str());
    }
};

#endif //IMAGE_STEGANOGRAPHY_LSBRECORDER_HPP