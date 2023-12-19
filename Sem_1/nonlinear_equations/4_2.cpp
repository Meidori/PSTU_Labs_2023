#include <iostream>
#include <cmath>
using namespace std;


// Вариант 4
// 0,25x^3 + x - 1,2502 = 0
// [0; 2]

// Метод Ньютона (метод касательных)

// f(x) = 0,25x^3 + x - 1,2502
// f'(x) = 0.75x^2 + 1
// f''(x) = 1.5x

int main() {
    float x, xPrev;
    // проверяем, берем ли мы сначала a или b за начальное значение x
    // f(b) * f''(b) > 0
    // (0.25 * 2^3 + 2 - 1.2502) * (1.5 * 2) > 0 => x0 = b;
    x = 2;
    xPrev = 0;
    double eps = 0.000001;

    while (abs(x - xPrev) > eps) {
        xPrev = x;
        x = xPrev - ((0.25 * pow(xPrev, 3) + xPrev - 1.2502) / (0.75 * pow(xPrev, 2) + 1));
    }
    cout << "Корень: " << x << endl;

    return 0;
}
