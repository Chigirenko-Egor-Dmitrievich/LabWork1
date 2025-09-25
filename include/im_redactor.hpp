/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

/**
 * @file im_redactor.hpp
 * @brief Image manipulation functions declarations.
 */

#ifndef IM_REDACTOR_HPP
#define IM_REDACTOR_HPP

#include "plugins.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
#include <thread>

/**
 * @enum RotationDirection
 * @brief Specifies the direction of image rotation.
 */
enum class RotationDirection
{
    Clockwise,
    CounterClockwise
};

/**
 * @brief Rotates a BMP image by 90 degrees in the specified direction.
 * 
 * @param image The BMPImage to rotate.
 * @param direction The rotation direction (Clockwise or CounterClockwise).
 */
void rotateImage(BMPImage& image, RotationDirection direction);


/**
 * @brief Applies a Gaussian blur filter to a BMP image.
 * 
 * @param image The BMPImage to filter.
 * @param coreSize The size of the core (must be odd).
 * @param sigma (σ) The standard deviation for the Gaussian function.
 */
void applyGaussianFilter(BMPImage& image, int coreSize, float σ);

#endif
