#include <iostream>

#include "vector.h"
#include "error.h"


int main() {
    try {
        Vector vect1(3);
        std::cout << "vect1: ";
        std::cout << vect1 << std::endl;

        int index;
        std::cout << "Index: ";
        std::cin >> index;
        std::cout << vect1[index] << std::endl;

        int step;
        std::cout << "Step: ";
        std::cin >> step;

        std::cout << "vect1 + step: ";
        std::cout << vect1 + step << std::endl;

        int size;
        std::cout << "Введите размер вектора (MAX_SIZE = 30): ";
        std::cin >> size;
        Vector vect2(size);
        std::cout << "vect2: ";
        std::cout << vect2 << std::endl; 
        
    }
    catch (Error& error) {
        error.what();
    }


    return 0;
}