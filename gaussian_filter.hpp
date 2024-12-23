/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#ifndef GAUSSIAN_FILTER_HPP
#define GAUSSIAN_FILTER_HPP

#include "debug_plugin.hpp"
#include <cmath>
#include <algorithm>
#include <vector>

void applyGaussianFilter(BMPImage& image, int coreSize, float σ)
{
    int width = image.getWidth();
    int length = image.getLength();

    std::vector<std::vector<float>> core(coreSize, std::vector<float>(coreSize));
    int halfSize = coreSize / 2;
    float sum = 0.0;

    for (int i = -halfSize; i <= halfSize; ++i)
    {
        for (int j = -halfSize; j <= halfSize; ++j)
        {
            core[i + halfSize][j + halfSize] = exp(-(i * i + j * j) / (2 * σ * σ));
            sum += core[i + halfSize][j + halfSize];
        }
    }

    for (int i = 0; i < coreSize; ++i)
    {
        for (int j = 0; j < coreSize; ++j)
        {
            core[i][j] /= sum;
        }
    }

    std::vector<RGB> filteredPixels(width * length);

    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float red = 0.0f;
            float green = 0.0f;
            float blue = 0.0f;

            for (int ky = -halfSize; ky <= halfSize; ++ky)
            {
                for (int kx = -halfSize; kx <= halfSize; ++kx)
                {
                    int nx = std::clamp(x + kx, 0, width - 1);
                    int ny = std::clamp(y + ky, 0, length - 1);

                    float weight = core[ky + halfSize][kx + halfSize];
                    const RGB& neighbor = image.getPixel(nx, ny);

                    red += neighbor.r * weight;
                    green += neighbor.g * weight;
                    blue += neighbor.b * weight;
                }
            }

            RGB& outputPixel = filteredPixels[y * width + x];
            outputPixel.r = static_cast<uint8_t>(std::clamp(red, 0.0f, 255.0f));
            outputPixel.g = static_cast<uint8_t>(std::clamp(green, 0.0f, 255.0f));
            outputPixel.b = static_cast<uint8_t>(std::clamp(blue, 0.0f, 255.0f));
        }
    }

    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            image.setPixel(x, y, filteredPixels[y * width + x]);
        }
    }
}

#endif

