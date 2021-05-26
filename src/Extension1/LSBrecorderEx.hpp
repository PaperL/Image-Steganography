//
// Created by Libro on 2021/5/25.
//

#ifndef IMAGE_STEGANOGRAPHY_LSBRECORDEREX_HPP
#define IMAGE_STEGANOGRAPHY_LSBRECORDEREX_HPP

#include "LBitmap1.h"
#include <string>
#include <cmath>
#include <iostream>
#include <vector>

template<bool encrypt = true, int Channel = 1>
class LSBrecorderEx {
public:
    std::string input, output;
    ln::LBitmap1 image;
    int X, Y, x, y, k, num, bitNum;
    double threshold = 2;
    int *father, *count;

    struct Pixel {
        double P[3];

        Pixel() {
            P[0] = P[1] = P[2] = 0;
        }

        Pixel(unsigned char R, unsigned char G, unsigned char B) {
            P[0] = R, P[1] = G, P[2] = B;
        }
    };

    int getFather(int v) {
        if (father[v] == v) return v;
        return father[v] = getFather(father[v]);
    }


    int calcBitNum(int x, int y) {
        int u = y * X + x;
        int fu = getFather(u);
        if (count[fu] > 30) return 2;
        return 3;
    }

    void connect(int u, int v) {
        int fu = getFather(u), fv = getFather(v);
        if (fu != fv) {
            father[fu] = fv;
            count[fv] += count[fu];
        }
    }

    double dist(unsigned char *pu, unsigned char *pv) {
        double res = 0;
        for (int i = 0; i < 3; ++i) {
            res += int(pu[i] - pv[i]) * (pu[i] - pv[i]);
        }
        return sqrt(res);
    }

    void prepare() {
        int u, v;
        unsigned char *p,*pp, pu[3], pv[3];
        for (int i = 0; i < Y; ++i)
            for (int j = 0; j < X; ++j) {
                if (i > 0) {
                    u = (i - 1) * X + j;
                    v = i * X + j;
                    p = image.Pixel(j, i - 1);
                    pp = image.Pixel(j, i);
                    for (int l = 0; l < 3; ++l) {
                        pu[l] = p[l] & ((unsigned char) 0b11111000);
                        pv[l] = pp[l] & ((unsigned char) 0b11111000);
                    }
                    if (dist(pu, pv) < threshold)connect(u, v);
                }
                if (j > 0) {
                    u = i * X + j - 1;
                    v = i * X + j;
                    p = image.Pixel(j-1, i);
                    pp = image.Pixel(j, i);
                    for (int l = 0; l < 3; ++l) {
                        pu[l] = p[l] & ((unsigned char) 0b11111000);
                        pv[l] = pp[l] & ((unsigned char) 0b11111000);
                    }
                    if (dist(pu, pv) < threshold)connect(u, v);
                }
            }
    }

public:
    LSBrecorderEx(const std::string &input, const std::string &output, int X, int Y) : input(input), output(output),
                                                                                       X(X),
                                                                                       Y(Y), x(0), y(0), k(0), num(0) {
        father = new int[X * Y];
        count = new int[X * Y];
        for (int i = 0; i < X * Y; ++i) {
            count[i] = 1;
            father[i] = i;
        }
        image.ReadBmp(input.c_str());
        prepare();
        bitNum = calcBitNum(0, 0);
    }

    LSBrecorderEx(const std::string &input, int X, int Y) : input(input), X(X),
                                                            Y(Y), x(0), y(0), k(0), num(0) {
        father = new int[X * Y];
        count = new int[X * Y];
        for (int i = 0; i < X * Y; ++i) {
            count[i] = 1;
            father[i] = i;
        }
        image.ReadBmp(input.c_str());
        prepare();
        bitNum = calcBitNum(0, 0);
    }

    int Capacity() {
        int res = 0;
        for (size_t y = 0; y < Y; ++y) {
            for (size_t x = 0; x < X; ++x) {
                res += calcBitNum(x, y) * 3;
            }
        }
        return res;
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
                bitNum = calcBitNum(x, y);
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
                bitNum = calcBitNum(x, y);
            }
        }
        return res;
    }

    ~LSBrecorderEx() {
        if (encrypt)
            image.WriteBmp(output.c_str());
        delete[] father;
        delete[] count;
    }
};

#endif //IMAGE_STEGANOGRAPHY_LSBRECORDEREX_HPP