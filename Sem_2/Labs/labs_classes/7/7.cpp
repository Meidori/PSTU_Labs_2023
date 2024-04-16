#include <iostream>

#include "vector.h"
#include "time.h"


int main() {
    Time time;
    std::cout << "Введите время - минуты и секунды:" << std::endl;
    std::cin >> time;
    std::cout << "time:" << std::endl;
    std::cout << time << std::endl;

    int size1 = 5;
    Vector<Time> vect1(size1, time);
    std::cout << "Введите элементы vect1 (тип Time):" << std::endl;
    std::cin >> vect1;
    std::cout << "vect1:" << std::endl;
    std::cout << vect1 << std::endl;;

    int size2 = 10;
    Vector<Time> vect2(size2, time);
    std::cout << "vect2(size2, time):" << std::endl;
    std::cout << vect2 << std::endl;
    vect2 = vect1;
    std::cout << "vect2 = vect1:" << std::endl;
    std::cout << vect2 << std::endl;

    int index, multiplier;
    std::cout << "Введите индекс:" << std::endl;
    std::cin >> index;
    std::cout << "Введите множитель:" << std::endl;
    std::cin >> multiplier;

    vect2[index] = vect2[index] * multiplier;
    std::cout << "vect2[index] = vect2[index] * multiplier:" << std::endl;
    std::cout << vect2[index] << std::endl;

    return 0;
}