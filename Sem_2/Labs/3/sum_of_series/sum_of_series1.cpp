#include <iostream>
#include <cmath>
using namespace std;
// Вариант 5


int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}


float sum_of_series(int n, int x) {
    if (n == 0) {
        return 1;
    }
    return (pow(x, n) / factorial(n)) + sum_of_series(n - 1, x);
}


int main() {
    int n;  // количество членов ряда
    cin >> n;
    int x;
    cin >> x;

    cout << sum_of_series(n - 1, x) << endl;

    return 0;
}   