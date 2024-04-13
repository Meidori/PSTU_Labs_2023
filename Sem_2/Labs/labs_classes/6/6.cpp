#include <iostream>

#include "vector.h"


int main() {
    int size1 = 5;
    Vector vect1(size1);
    std::cout << "Создан вектор (vect1) размера " << size1 << ":\n";
    std::cout << vect1 << std::endl;

    std::cout << "Введите значения элементов вектора:" << std::endl;
    std::cin >> vect1;

    std::cout << "vect1:" << std::endl;
    std::cout << vect1 << std::endl;

    int size2 = 10;
    Vector vect2(size2);
    std::cout << "Создан вектор (vect2) размера " << size2 << ":\n";
    std::cout << vect2 << std::endl;

    std::cout << "vect2 = vect1" << std::endl;
    vect2 = vect1;
    std::cout << "vect2:" << std::endl;
    std::cout << vect2 << std::endl;

    std::cout << "vect2[0]: " << vect2[0] << std::endl; 
    std::cout << "vect2[2]: " << vect2[2] << std::endl; 
    std::cout << "vect2[7]: " << vect2[7] << std::endl;

    int size3 = 7;
    Vector vect3(size3);
    std::cout << "Создан вектор (vect3) размера " << size3 << ":\n";
    std::cout << vect3 << std::endl;

    std::cout << "Размер вектора: vect3()" << std::endl;
    std::cout << vect3() << std::endl;

    std::cout << "Разыменовавыем значение vect1.get_first():" << std::endl;
    std::cout << *(vect1.get_first()) << std::endl; 

    std::cout << "Разыменовавыем значение vect2.get_last():" << std::endl;
    std::cout << *(vect2.get_last()) << std::endl; 

    std::cout << "Создан итератор, указывающий на первый элемент вектора vect1." << std::endl;
    Iterator i = vect1.get_first();
    std::cout << *(i) << std::endl;

    std::cout << "Увеличиваем итератор на 1." << std::endl;
    i = i + 1;
    std::cout << *(i) << std::endl;

    std::cout << "Увеличиваем итератор еще на 3." << std::endl;
    i = i + 3;
    std::cout << *(i) << std::endl;

    std::cout << "Уменьшаем итератор на 2." << std::endl;
    i = i - 2;
    std::cout << *(i) << std::endl;


    return 0;
}