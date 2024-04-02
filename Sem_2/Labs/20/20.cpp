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


    ~Equation() {
        std::cout << "Уравнение " << coefficient_A << "x^2 + " << coefficient_B << "x + " << coefficient_C << std::endl;
        std::cout << "Удалено из памяти." << std::endl;
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