#include <iostream>
#include "time.h"


int main() {
    Time time1;
    std::cout << "Введите минуты и секунды для объекта time1:" << std::endl;
    std::cin >> time1;
    std::cout << "time1:" << time1 << std:: endl;

    Time time2 = time1;
    std::cout << "Создан объект time2 и ему присвоено значение time1." << std::endl;
    
    int subtraction_seconds;
    std::cout << "Введите количество секунд, которое будет вычтено из time2:" << std::endl;
    std::cin >> subtraction_seconds;
    time2 = time2 - subtraction_seconds;
    std::cout << "time2:" << time2 << std:: endl;

    bool comparison;
    std::cout << "Результат операции сравнения time1 == time2:" << std::endl;
    comparison = time1 == time2;
    std::cout << comparison << std::endl;
    
    std::cout << "Результат операции сравнения time1 != time2:" << std::endl;
    comparison = time1 != time2;
    std::cout << comparison << std::endl;

    return 0;
}