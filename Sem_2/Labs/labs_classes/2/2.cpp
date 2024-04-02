#include <iostream>
#include "equation.h"


int main() {
    Equation equ1;
    std::cout << "Объект, созданный деструктором без параметров (по умолчанию):" << std::endl;
    equ1.show();

    double A, B, C;
    std::cout << "Введите коэффиценты A, B, C" << std::endl;
    std::cin >> A >> B >> C;
    Equation equ2(A, B, C);
    std::cout << "Объект, созданный деструктором c параметрами (" << A << ", " << B << ", " << C << "):" << std::endl;
    equ2.show();

    Equation equ3(A, B);
    std::cout << "Объект, созданный деструктором c параметрами (" << A << ", " << B << "):" << std::endl;
    equ3.show();
    
    Equation equ4(equ2);
    std::cout << "Объект, созданный деструктором копирования (equ4(equ2)):" << std::endl;
    equ4.show();

    return 0;
}