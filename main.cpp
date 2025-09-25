/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#include "plugins.hpp"
#include "rotate_image.hpp"
#include "gaussian_filter.hpp"
#include <iostream>

int main()
{
    BMPImage image;

    image.read("1.bmp");
    
    rotateImage(image, RotationDirection::Clockwise);
    image.save("2.bmp");

    rotateImage(image, RotationDirection::CounterClockwise);

    rotateImage(image, RotationDirection::CounterClockwise);
    image.save("3.bmp");

    rotateImage(image, RotationDirection::Clockwise);

    applyGaussianFilter(image, 5, 7);
    image.save("4.bmp");
  
    std::cout << "All operations completed successfully!" << std::endl;
    return 0;
}


