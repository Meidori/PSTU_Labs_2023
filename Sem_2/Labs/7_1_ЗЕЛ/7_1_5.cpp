#include <iostream>
#include <complex>
using namespace std;


template <typename N> 
N multiplication(N num1, N num2) {
    return num1 * num2;
}


int main() {
    float n1, n2;
    cout << "Введите первое вещественное число:" << endl;
    cin >> n1;
    cout << "Введите второе вещественное число:" << endl;
    cin >> n2;
    cout << "Результат умножения двух вещественных чисел: " << multiplication(n1, n2) << endl;


    double real1, real2, imag1, imag2;
    cout << "Введите действительную и мнимую часть первого числа через пробел:" << endl;
    cin >> real1 >> imag1;
    cout << "Введите действительную и мнимую часть второго числа через пробел:" << endl;
    cin >> real2 >> imag2;
    
    complex<double> z1(real1, imag1);
    complex<double> z2(real2, imag2); 
    
    cout << "Результат умножения двух комплексных чисел: " << multiplication(z1, z2) << endl;

    return 0;
}

