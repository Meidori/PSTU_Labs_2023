#include <iostream>
#include "equation.h"


int main() {
    Equation equ1;
    std::cout << "Объект equ1, созданный конструктором без параметров:" << std::endl;
    equ1.show();

    double A, B, C;
    std::cout << "Введите коэффиценты A, B, C" << std::endl;
    std::cin >> A >> B >> C;
    Equation equ2(A, B, C);
    std::cout << "Объект equ2, созданный конструктором c параметрами (" << A << ", " << B << ", " << C << "):" << std::endl;
    equ2.show();

    Equation equ3(A, B);
    std::cout << "Объект equ3, созданный конструктором c параметрами (" << A << ", " << B << "):" << std::endl;
    equ3.show();
    
    Equation equ4(equ2);
    std::cout << "Объект equ4, созданный конструктором копирования (equ4(equ2)):" << std::endl;
    equ4.show();

    return 0;
}