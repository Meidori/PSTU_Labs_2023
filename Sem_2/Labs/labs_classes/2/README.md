Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 2 - классы

> Будет добавлено позже

# 2.1 Код программы

> 2.cpp
```cpp
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
```

> equation.h
```cpp
#pragma once
#include <iostream>


class Equation {
private:
    double coefficient_A;
    double coefficient_B;
    double coefficient_C;


public:
    Equation(double A = 0, double B = 0, double C = 0) {
        coefficient_A = A;
        coefficient_B = B;
        coefficient_C = C;
    }


    Equation(const Equation& equ) {
        coefficient_A = equ.coefficient_A;
        coefficient_B = equ.coefficient_B;
        coefficient_C = equ.coefficient_C;
    }



    ~Equation() {
        std::cout << "Уравнение " << coefficient_A << "x^2 + " << coefficient_B << "x + " << coefficient_C;
        std::cout << " удалено из памяти." << std::endl;
    }


    void show() {
        std::cout << coefficient_A << "x^2 + " << coefficient_B << "x + " << coefficient_C << std::endl;
    }


    void set_A(double A) {
        coefficient_A = A;
    }


    void set_B(double B) {
        coefficient_B = B;
    }


    void set_C(double C) {
        coefficient_C = C;
    }


    void get_A() {
        std::cout << coefficient_A << std::endl;
    }


    void get_B() {
        std::cout << coefficient_B << std::endl;
    }


    void get_C() {
        std::cout << coefficient_C << std::endl;
    }
};
```

# 2.2 UML

# Пример работы

```
Объект equ1, созданный конструктором без параметров:
0x^2 + 0x + 0
Введите коэффиценты A, B, C
1 2 3
Объект equ2, созданный конструктором c параметрами (1, 2, 3): 
1x^2 + 2x + 3
Объект equ3, созданный конструктором c параметрами (1, 2):    
1x^2 + 2x + 0
Объект equ4, созданный конструктором копирования (equ4(equ2)):
1x^2 + 2x + 3
Уравнение 1x^2 + 2x + 3 удалено из памяти.
Уравнение 1x^2 + 2x + 0 удалено из памяти.
Уравнение 1x^2 + 2x + 3 удалено из памяти.
Уравнение 0x^2 + 0x + 0 удалено из памяти.
```

# Вопросы
