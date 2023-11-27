#include <iostream>
#include <cmath>
using namespace std;


int main() {
    int N, s;
    bool flag = 0;
    cout << "Введите число N" << endl;
    cin >> N;
    cout << "Введите цифру s" << endl;
    cin >> s;
    
    while (N != 0) {
        if (N % 10 == s) {
            flag = 1;
            break;
        }
        N /= 10;
    }

    if (flag == 1) {
        cout << "Цифра содержиться в числе" << endl;
    }
    else {
        cout << "Цифра не содержиться в числе" << endl; 
    }

    return 0;
}   