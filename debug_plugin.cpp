/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#include "debug_plugin.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

void BMPImage::updateHeaders()
{
    infoHeader.biWidth = width;
    infoHeader.biLength = length;
    infoHeader.biSizeImage = width * length * sizeof(RGB);
    fileHeader.bfSize = fileHeader.bfOffBits + infoHeader.biSizeImage;
}

bool BMPImage::read(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: file opening failure" << std::endl;
        std::cerr << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42)
    {
        std::cerr << "Error: the file format does not match the BMP format" << std::endl;
        std::cerr << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    width = infoHeader.biWidth;
    length = abs(infoHeader.biLength);

    if (fileHeader.bfOffBits < sizeof(fileHeader) + infoHeader.biSize)
    {
        std::cerr << "Error: invalid bfOffBits value" << std::endl;
        std::cerr << std::endl;
        return false;
    }

    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    int rowPadding = (4 - (width * 3) % 4) % 4;

    pixels.resize(width * length);
    for (int y = 0; y < length; ++y)
    {
        file.read(reinterpret_cast<char*>(&pixels[y * width]), width * sizeof(RGB));
        file.ignore(rowPadding);
    }

    return true;
}

void BMPImage::save(const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error: output file creating failure" << std::endl;
        std::cerr << std::endl;
        return;
    }

    int rowPadding = (4 - (width * 3) % 4) % 4;
    infoHeader.biSizeImage = (width * 3 + rowPadding) * abs(length);
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + infoHeader.biSizeImage;

    outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int y = 0; y < abs(length); ++y)
    {
        outFile.write(reinterpret_cast<char*>(&pixels[y * width]), width * sizeof(RGB));
        outFile.write("\0", rowPadding);
    }

    outFile.close();
}

RGB BMPImage::getPixel(int x, int y) const
{
    if ((x >= 0) && (x < width) && (y >= 0) && (y < length))
    {
        return pixels[y * width + x];
    }
    throw std::out_of_range("Error: pixel coordinates out of range");
}

void BMPImage::setPixel(int x, int y, const RGB& color)
{
    if ((x >= 0) && (x < width) && (y >= 0) && (y < length))
    {
        pixels[y * width + x] = color;
    }

    else
    {
        throw std::out_of_range("Error: pixel coordinates out of range");
    }
}

void BMPImage::setPixels(const std::vector<RGB>& newPixels)
{
    if (newPixels.size() == pixels.size())
    {
        pixels = newPixels;
    }

    else
    {
        throw std::invalid_argument("Error: new pixel data size does not match current size");
    }
}

void BMPImage::setDimensions(int w, int l)
{
    if ((w > 0) && (l > 0))
    {
        width = w;
        length = l;
        pixels.resize(width * length);
        updateHeaders();
    }

    else
    {
        throw std::invalid_argument("Error: width or length is negative");
    }
}
