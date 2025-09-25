/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

/**
 * @file plugins.cpp
 * @brief Implementation of BMPImage class methods.
 */

#include "../include/plugins.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

/**
 * @brief Updates the BMP file and info headers based on current image dimensions.
 */
void BMPImage::updateHeaders()
{
    infoHeader.biWidth = width;
    infoHeader.biLength = length;
    infoHeader.biSizeImage = width * length * sizeof(RGB);
    fileHeader.bfSize = fileHeader.bfOffBits + infoHeader.biSizeImage;
}

/**
 * @brief Reads a BMP image from a file.
 * 
 * @param filename The name of the BMP file to read.
 * @return true if the file was read successfully, false otherwise.
 */
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

    size_t extraSize = fileHeader.bfOffBits - (sizeof(fileHeader) + sizeof(infoHeader));
    extraData.resize(extraSize);
    if (extraSize > 0)
    {
        file.read(reinterpret_cast<char*>(extraData.data()), extraSize);
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

/**
 * @brief Saves the BMP image to a file.
 * 
 * @param filename The name of the output BMP file.
 */
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
    
    fileHeader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + extraData.size() + infoHeader.biSizeImage;

    outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    
    if (!extraData.empty())
    {
        outFile.write(reinterpret_cast<const char*>(extraData.data()), extraData.size());
    }

    for (int y = 0; y < abs(length); ++y)
    {
        outFile.write(reinterpret_cast<char*>(&pixels[y * width]), width * sizeof(RGB));
        outFile.write("\0", rowPadding);
    }

    outFile.close();
}

/**
 * @brief Gets the RGB pixel at the specified coordinates.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return RGB The pixel value.
 * @throws std::out_of_range if coordinates are out of bounds.
 */
RGB BMPImage::getPixel(int x, int y) const
{
    if ((x >= 0) && (x < width) && (y >= 0) && (y < length))
    {
        return pixels[y * width + x];
    }
    throw std::out_of_range("Error: pixel coordinates out of range");
}

/**
 * @brief Sets the RGB pixel at the specified coordinates.
 * 
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The new RGB pixel value.
 * @throws std::out_of_range if coordinates are out of bounds.
 */
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

/**
 * @brief Sets all pixels in the image.
 * 
 * @param newPixels The new pixel data.
 * @throws std::invalid_argument if the new pixel data size doesn't match the current size.
 */
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

/**
 * @brief Sets the dimensions of the image and resizes the pixel buffer.
 * 
 * @param w The new width.
 * @param h The new length.
 * @throws std::invalid_argument if width or length are not positive.
 */
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
