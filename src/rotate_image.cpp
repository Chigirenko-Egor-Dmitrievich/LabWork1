/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

/**
 * @file rotate_image.cpp
 * @brief Implementation of image rotation functions.
 */

/**
 * @enum RotationDirection
 * @brief Specifies the direction of image rotation.
 */

/**
 * @brief Rotates a BMP image by 90 degrees in the specified direction.
 * 
 * @param image The BMPImage to rotate.
 * @param direction The rotation direction (Clockwise or CounterClockwise).
 * 
 * The function:
 * 1. Creates a temporary buffer for rotated pixels.
 * 2. Splits the image into segments for parallel processing.
 * 3. Uses multiple threads to rotate each segment.
 * 4. Combines results and updates image dimensions.
 */


#include "../include/plugins.hpp"
#include <vector>
#include <thread>

enum class RotationDirection
{
    Clockwise,
    CounterClockwise
};

void rotateImage(BMPImage& image, RotationDirection direction)
{
    int width = image.getWidth();
    int length = image.getLength();
    std::vector<RGB> rotatedPixels(width * length);

    const unsigned int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    auto rotate_segment = [&](int start_y, int end_y)
    {
        for (int y = start_y; y < end_y; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                if (direction == RotationDirection::Clockwise)
                {
                    rotatedPixels[(width - x - 1) * length + y] = image.getPixel(x, y);
                }

                else
                {
                    rotatedPixels[x * length + (length - y - 1)] = image.getPixel(x, y);
                }
            }
        }
    };
    
    int rows_per_thread = length / num_threads;
    for (unsigned int i = 0; i < num_threads; ++i)
    {
    	int start_y = i * rows_per_thread;
    	int end_y = (i == num_threads - 1) ? length : (i+1) * rows_per_thread;
    	threads.emplace_back(rotate_segment, start_y, end_y);
    }
    
    for (auto& thread : threads) thread.join();

    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            image.setPixel(x, y, rotatedPixels[y * width + x]);
        }
    }

    image.setDimensions(length, width);
}
