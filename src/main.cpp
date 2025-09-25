/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#include "../include/plugins.hpp"
#include "../include/im_redactor.hpp"
#include <iostream>

int main()
{
    BMPImage image;

    image.read("Images/1.bmp");
    
    rotateImage(image, RotationDirection::Clockwise);
    image.save("Images/2.bmp");

    rotateImage(image, RotationDirection::CounterClockwise);

    rotateImage(image, RotationDirection::CounterClockwise);
    image.save("Images/3.bmp");

    rotateImage(image, RotationDirection::Clockwise);

    applyGaussianFilter(image, 5, 7.0f);
    image.save("Images/4.bmp");
  
    std::cout << "All operations completed successfully! You can find new images in the folder `Images`!" << std::endl;
    return 0;
}


