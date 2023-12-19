#include <iostream>
#include <cmath>
using namespace std;


// Вариант 4
// 0,25x^3 + x - 1,2502 = 0
// [0; 2]

// Метод половинного деления
int main() {
    float a, b, c;
    float fA, fB, fC;
    double eps = 0.000001;

    a = 0;
    b = 2;

    while (b - a > eps) {
        c = (a + b) / 2;
        fA = 0.25 * pow(a, 3) + a - 1.2502;
        fB = 0.25 * pow(b, 3) + b - 1.2502;
        fC = 0.25 * pow(c, 3) + c - 1.2502;

        if (fA * fC < 0) {
            b = c;
        }
        else if (fB * fC < 0) {
            a = c;
        }
    }

    cout << "Корни: " << a << "; " << b << endl;
    return 0;
}