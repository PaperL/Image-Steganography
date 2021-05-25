#ifndef LN_BITMAP_H
#define LN_BITMAP_H 1

#include <stdlib.h>
#include <stdio.h>

namespace ln {
    //返回24bit并且做了32位对齐的图像一行所占的字节数
    int CalStride24(int width);

    //m_pixel中存储的图像是正立的
    //像素分布，从左往右分别为BGRA
    class LBitmap1 {
    public:
        LBitmap1();

        /*
        *  
        * bpp == 4
        */
        LBitmap1(int w, int h, int bpp, unsigned char *pixel = NULL);

        ~LBitmap1();

        bool IsValid() const;

        LBitmap1 *Clone() const;

        //将bpp==4转化为bpp==3
        //这个函数里可以将alpha值与白色一起来生成bmp==3的图像
        int Conver32To24();

        //将bpp==3转化为bpp==4
        int Conver24To32();

        const int Width() { return m_width; }

        const int Height() { return m_height; }

        const int Bpp() { return m_bpp; }

        unsigned char *Pixel() { return m_pixel; }

        unsigned char *Pixel(int x, int y);

        //一行像素所占的字节数
        int Stride() const;

        //整个图像像素所占的字节数
        int GetSize() const;

        static bool ReadBmpSize(const char *path, int *width, int *height);

        static bool IsBmpFile(const char *filename);

        bool ReadBmp(const char *filename);

        bool WriteBmp(const char *filename);

    private:
        void Reset();

    private:
        unsigned char *m_pixel;
        int m_width;
        int m_height;
        int m_bpp;    //3 或者4，对应24或者32
    };

}

#endif
