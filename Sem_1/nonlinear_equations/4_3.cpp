#include <iostream>
#include <cmath>
using namespace std;


// Вариант 4
// 0,25x^3 + x - 1,2502 = 0
// [0; 2]

// Метод итераций

// f(x) = 0,25x^3 + x - 1,2502
// f'(x) = 0.75x^2 + 1
// f''(x) = 1.5x
// ф(x) = x + λ(0,25x^3 + x - 1,2502)
// -1/r < λ < 0, если f'(x) > 0
// 0 < λ < 1/r, если f'(x) < 0
// r = max(|f'(a)|, |f'(b)|)
// r = max((0.75 * 0 + 1), (0.75 * 4 + 1)) => r = 4
// f'(x) > 0 => -1/r < λ < 0
// Берем удобное число из диапозона: λ = -1/5 = -0.2



int main() {
    float x, xPrev;
    double lambda = -0.1, eps = 0.000001;
    x = 2;
    xPrev = 0;  // берем заведомо меньше x

    while (abs(x - xPrev) > eps) {
        xPrev = x;
        x = lambda * (0.25 * pow(xPrev, 3) + xPrev - 1.2502) + xPrev;
    }

    cout << "Корень: " << x << endl;
    return 0;
}