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