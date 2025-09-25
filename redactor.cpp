/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#include "plugins.hpp"
#include "rotate_image.hpp"
#include "gaussian_filter.hpp"
#include "show_options.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    BMPImage image;

    std::string filename;
    std::cout << "Enter the name of the input file: ";
    std::cin >> filename;
    std::cout << std::endl;

    if (!image.read(filename))
    {
        std::cerr << "Error: BMP file reading failure!" << std::endl;
        std::cerr << std::endl;
        return 1;
    }

    bool ongoing = true;
    while (ongoing)
    {
        showOptoins();
        int command;
        std::cout << "Enter command: ";
        std::cin >> command;
        std::cout << std::endl;

        switch (command)
        {
            case 1:
            {
                rotateImage(image, RotationDirection::Clockwise);
                std::cout << "An image was rotated clockwise by 90 degrees" << std::endl;
                std::cout << std::endl;
                break;

            }

            case 2:
            {
                rotateImage(image, RotationDirection::CounterClockwise);
                std::cout << "An image was rotated counterclockwise by 90 degrees" << std::endl;
                std::cout << std::endl;
                break;
            }

            case 3:
            {
                int coreSize;
                float σ;

                std::cout << "Enter odd number - core size: ";
                std::cin >> coreSize;
                std::cout << std::endl;

                if (coreSize % 2 == 0)
                {
                    std::cout << "Error: even number - core size - given" << std::endl;
                    std::cout << std::endl;
                    break;
                }

                std::cout << "Enter standard deviation - sigma (σ): ";
                std::cin >> σ;
                std::cout << std::endl;

                applyGaussianFilter(image, coreSize, σ);
                std::cout << "Gaussian filter applied" << std::endl;
                std::cout << std::endl;
                break;
            }

            case 4:
            {
                std::string outputFilename;
                std::cout << "Enter the name of the output file: ";
                std::cin >> outputFilename;
                std::cout << std::endl;

                image.save(outputFilename);
                std::cout << "Image saved as " << outputFilename << std::endl;
                std::cout << std::endl;
                break;
            }

            case 5:
            {
                std::cout << "Have a Nice Day! 🌺" << std::endl;
                std::cout << std::endl;
                ongoing = false;
                break;
            }

            default:
            {
                std::cout << "Error: invalid command" << std::endl;
                std::cout << std::endl;
                break;
            }
        }
    }

    return 0;
}
