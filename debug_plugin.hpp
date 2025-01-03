/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#ifndef DEBUG_PLUGIN_HPP
#define DEBUG_PLUGIN_HPP

#include <vector>
#include <string>
#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biLength;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class BMPImage
{
    private:
        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;
        std::vector<RGB> pixels;
        int width;
        int length;

        void updateHeaders();

    public:
        bool read(const std::string& filename);

        void save(const std::string& filename);

        int getWidth() const
        {
        return width;
        }
        
        int getLength() const
        {
        return length;
        }

        RGB getPixel(int x, int y) const;
        void setPixel(int x, int y, const RGB& color);
        void setPixels(const std::vector<RGB>& newPixels);
        void setDimensions(int w, int l);

        const BMPInfoHeader& getInfoHeader() const
        {
        return infoHeader;
        }

        const BMPFileHeader& getFileHeader() const
        {
        return fileHeader;
        }
};

#endif

