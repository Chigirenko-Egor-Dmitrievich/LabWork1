/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#ifndef ROTATE_IMAGE_HPP
#define ROTATE_IMAGE_HPP

#include "debug_plugin.hpp"

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

    for (int y = 0; y < length; ++y)
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

    for (int y = 0; y < length; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            image.setPixel(x, y, rotatedPixels[y * width + x]);
        }
    }

    image.setDimensions(length, width);
}

#endif
