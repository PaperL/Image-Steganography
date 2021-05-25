#include "LBitmap1.h"
#include <string>
#include <cstring>
#include <fstream>
#include <errno.h>

namespace ln {
    typedef struct tagBITMAPINFOHEADER {
        unsigned int biSize;
        int biWidth;
        int biHeight;
        unsigned short biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        int biXPelsPerMeter;
        int biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
    } BITMAPINFOHEADER;

#pragma pack(push)
#pragma pack(2)
    typedef struct tagBITMAPFILEHEADER {
        unsigned short bfType;  //2
        unsigned int bfSize;    //4
        unsigned short bfReserved1; //2
        unsigned short bfReserved2; //2 
        unsigned int bfOffBits;   //4
    } BITMAPFILEHEADER;
#pragma pack(pop)

    static bool readBmpSize(const char *path, int *width, int *height, int *offset, int *bitCount) {
        FILE *in_file = NULL;
        in_file = fopen(path, "rb");
        // _wfopen_s(&in_file, path, L"rb");

        if (!in_file) {

            if (width) *width = 0;
            if (height) *height = 0;
            if (bitCount) *bitCount = 0;
            return false;
        }

        BITMAPFILEHEADER file_head;

        int s1 = sizeof(file_head);
        fread(&file_head, s1, 1, in_file);

        BITMAPINFOHEADER bmp_head;
        int s2 = sizeof(bmp_head);
        fread(&bmp_head, s2, 1, in_file);

        if (bitCount) *bitCount = bmp_head.biBitCount;

        fclose(in_file);

        if (file_head.bfType != 19778) {
            printf("readbmp_error: no have BM\n");

            if (width) *width = 0;
            if (height) *height = 0;
            return false;
        }
        if (width) {
            *width = bmp_head.biWidth;
        }
        if (height) {
            *height = bmp_head.biHeight;
        }

        if (offset) {
            *offset = file_head.bfOffBits;
        }

        return true;
    }

    int CalStride24(int width) {
        return ((width * 24 + 31) & ~31) >> 3;
    }


    LBitmap1::LBitmap1()
            :
            m_pixel(NULL),
            m_width(0),
            m_height(0),
            m_bpp(3) {

    }

    LBitmap1::LBitmap1(int w, int h, int bpp, unsigned char *pixel)
            :
            m_pixel(0),
            m_width(w),
            m_height(h),
            m_bpp(bpp) {
        int s;
        if (bpp == 1) {
            s = w * h;
        }
        else {
            s = Stride() * m_height;
        }

        m_pixel = new unsigned char[s];

        if (pixel == NULL) {
            memset(m_pixel, 0, s);
        }
        else {
            memcpy(m_pixel, pixel, s);
        }


    }

    LBitmap1::~LBitmap1() {
        Reset();
    }

    void LBitmap1::Reset() {
        if (m_pixel) {
            delete[] m_pixel;
            m_pixel = NULL;
        }
        m_width = 0;
        m_height = 0;
        m_bpp = 0;
    }

    bool LBitmap1::IsValid() const {
        return m_width > 0 && m_height > 0;
    }

    LBitmap1 *LBitmap1::Clone() const {
        if (IsValid()) {
            LBitmap1 *bmp = new LBitmap1;
            bmp->m_width = this->m_width;
            bmp->m_height = this->m_height;
            bmp->m_bpp = this->m_bpp;

            int s = GetSize();

            bmp->m_pixel = new unsigned char[s];
            memcpy(bmp->m_pixel, m_pixel, s);

            return bmp;
        }
        return NULL;
    }

    int LBitmap1::Conver32To24() {
        if (m_bpp == 4 && m_pixel) {
            int s = CalStride24(m_width);
            unsigned char *bit24 = new unsigned char[s * m_height];

            for (int j = 0; j < m_height; ++j) {
                for (int i = 0; i < m_width; ++i) {
                    unsigned char *p0 = m_pixel + j * m_width * 4 + i * 4;
                    unsigned char *p2 = bit24 + j * s + i * 3;
                    double alpha = *(p0 + 3) / 255.0;
                    //double alpha = 1;

                    *p2 = (unsigned char) (*p0 * alpha + 255 * (1 - alpha));
                    *(p2 + 1) = (unsigned char) (*(p0 + 1) * alpha + 255 * (1 - alpha));
                    *(p2 + 2) = (unsigned char) (*(p0 + 2) * alpha + 255 * (1 - alpha));

                    //*p2 = *p0;
                    //*(p2+1) = *(p0+1);
                    //*(p2+2) = *(p0+2);
                }
            }

            delete[] m_pixel;

            m_pixel = bit24;
            m_bpp = 3;

            return 0;
        }

        return 1;
    }

    int LBitmap1::Conver24To32() {
        if (m_bpp == 3 && m_pixel) {
            int s = CalStride24(m_width);
            unsigned char *bit32 = new unsigned char[m_width * m_height * 4];

            for (int j = 0; j < m_height; ++j) {
                for (int i = 0; i < m_width; ++i) {
                    unsigned char *p0 = m_pixel + j * s + i * 3;
                    unsigned char *p2 = bit32 + j * m_width * 4 + i * 4;
                    *p2 = *p0;
                    *(p2 + 1) = *(p0 + 1);
                    *(p2 + 2) = *(p0 + 2);
                    *(p2 + 3) = 255;

                }
            }
            delete[] m_pixel;

            m_pixel = bit32;
            m_bpp = 4;
            return 0;
        }
        return 1;
    }

    unsigned char *LBitmap1::Pixel(int x, int y) {
        return m_pixel + y * Stride() + x * m_bpp;
    }

    int LBitmap1::Stride() const {
        if (m_bpp == 4) {
            return m_width * 4;
        }
        else {
            return CalStride24(m_width);
        }
    }

    int LBitmap1::GetSize() const {
        return Stride() * m_height;
    }

    //////////////////////////////////////////////////////////////////////////
    // bmp
    bool LBitmap1::ReadBmpSize(const char *path, int *width, int *height) {
        return readBmpSize(path, width, height, NULL, NULL);
    }

    bool LBitmap1::IsBmpFile(const char *filename) {
        int w, h;
        LBitmap1::ReadBmpSize(filename, &w, &h);

        if (w > 0 && h > 0) {
            return true;
        }
        return false;
    }

    bool LBitmap1::ReadBmp(const char *filename) {
        Reset();

        int w, h, offset, bitCount;

        if (!readBmpSize(filename, &w, &h, &offset, &bitCount)) {
            return false;
        }

        FILE *in_file = NULL;
        in_file = fopen(filename,"rb");
        // _wfopen_s(&in_file, filename, L"rb");

        if (!in_file) {
            return false;
        }

        fseek(in_file, offset, 0);

        if (bitCount == 24) {
            int stride24 = CalStride24(w);
            int stride32 = w * 4;
            unsigned char *temp_line = new unsigned char[stride24];

            m_pixel = new unsigned char[stride32 * h];
            unsigned char *p2 = m_pixel + (h - 1) * stride32;

            for (int j = 0; j < h; ++j) {
                fread(temp_line, stride24, 1, in_file);

                unsigned char *pp2 = p2;
                unsigned char *pp0 = temp_line;

                for (int i = 0; i < w; ++i) {
                    *(pp2) = *(pp0);
                    *(pp2 + 1) = *(pp0 + 1);
                    *(pp2 + 2) = *(pp0 + 2);
                    *(pp2 + 3) = 255;

                    pp0 += 3;
                    pp2 += 4;
                }
                p2 -= stride32;
            }
            m_bpp = 4;
            delete[] temp_line;
        }
        m_width = w;
        m_height = h;
        return true;
    }

    bool LBitmap1::WriteBmp(const char *filename) {
        if (m_bpp == 3) {
            LBitmap1 *b = Clone();
            b->Conver24To32();
            bool r = b->WriteBmp(filename);
            delete b;
            return r;
        }

        FILE *out_file = NULL;
        out_file = fopen(filename,"wb");
        // _wfopen_s(&out_file, filename, L"wb");

        if (!out_file) {
            return false;
        }
        int h = m_height;

        if (h < 0) {
            h = -h;
        }
        int stride24 = CalStride24(m_width);
        int stride32 = m_width * 4;

        BITMAPINFOHEADER bmp_head = {0};
        bmp_head.biSize = sizeof(bmp_head);
        bmp_head.biWidth = m_width;
        bmp_head.biHeight = m_height;
        bmp_head.biPlanes = 1;
        bmp_head.biBitCount = 24;
        bmp_head.biSizeImage = stride24 * h;

        BITMAPFILEHEADER file_head;
        file_head.bfType = 19778;
        file_head.bfReserved1 = 0;
        file_head.bfReserved2 = 0;
        file_head.bfOffBits = sizeof(file_head) + sizeof(bmp_head);
        file_head.bfSize = file_head.bfOffBits + bmp_head.biSizeImage;

        int s1 = fwrite(&file_head, sizeof(file_head), 1, out_file);
        int s2 = fwrite(&bmp_head, sizeof(bmp_head), 1, out_file);

        unsigned char *temp_line = new unsigned char[stride24];
        unsigned char *p0 = m_pixel + (m_height - 1) * stride32;

        for (int j = 0; j < h; ++j) {

            unsigned char *p2 = temp_line;
            unsigned char *pp0 = p0;

            for (int i = 0; i < m_width; ++i) {
                *p2 = *pp0;
                *(p2 + 1) = *(pp0 + 1);
                *(p2 + 2) = *(pp0 + 2);

                pp0 += 4;
                p2 += 3;
            }
            p0 -= stride32;
            fwrite(temp_line, stride24, 1, out_file);
        }
        fclose(out_file);

        delete[] temp_line;
        return true;
    }
} // end namespcae ln
