/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

/**
 * @file gaussian_filter.cpp
 * @brief Implementation of Gaussian blur filter.
 */

/**
 * @brief Applies a Gaussian blur filter to a BMP image.
 * 
 * @param image The BMPImage to filter.
 * @param coreSize The size of the core (must be odd).
 * @param sigma (σ) The standard deviation for the Gaussian function.
 * 
 * The function:
 * 1. Generates a Gaussian core based on the specified size and sigma (σ).
 * 2. Normalizes the core values.
 * 3. Splits the image into segments for parallel processing.
 * 4. Uses multiple threads to apply the filter to each segment.
 * 5. Combines results and updates the image.
 */

#include "../include/plugins.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <thread>

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
    const unsigned int num_threads = 1;
    std::vector<std::thread> threads;
     
    auto process_segment = [&](int start_y, int end_y)
    {
    	for (int y = start_y; y < end_y; ++y)
    	{
            for (int x = 0; x < width; ++x)
            {
                float red = 0.0f, green = 0.0f, blue = 0.0f;

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
    };

    int rows_per_thread = length / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i)
    {
    	int start_y = i * rows_per_thread;
    	int end_y = (i == num_threads - 1) ? length : (i + 1) * rows_per_thread;
    	threads.emplace_back(process_segment, start_y , end_y);
    }
    
    for (auto& thread : threads) thread.join();
	
    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            image.setPixel(x, y, filteredPixels[y * width + x]);
        }
    }
}

