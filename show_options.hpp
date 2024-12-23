/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork1
*/

#ifndef SHOW_OPTIONS_HPP
#define SHOW_OPTIONS_HPP

#include <iostream>

void showOptoins()
{
    std::cout << " --------------------------------------------" << std::endl;
    std::cout << " | Optoins:                                 |" << std::endl;
    std::cout << " --------------------------------------------" << std::endl;
    std::cout << " | 1. Rotate clockwise by 90 degrees        |" << std::endl;
    std::cout << " | 2. Rotate counterclockwise by 90 degrees |" << std::endl;
    std::cout << " | 3. Apply Gaussian filter                 |" << std::endl;
    std::cout << " | 4. Save image                            |" << std::endl;
    std::cout << " | 5. End of programm                       |" << std::endl;
    std::cout << " --------------------------------------------" << std::endl;
    std::cout << std::endl;
}

#endif
