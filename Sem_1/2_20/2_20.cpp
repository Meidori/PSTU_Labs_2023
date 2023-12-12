#include <iostream>
#include <cmath>
using namespace std;


int main() {
    float S, a, N;
    bool flag = 0;
    cin >> N >> S;
    
    for (int i = 1; i <= N; i++) {
        a = sin(N + (i / N));
        a = round(a * 10) / 10;
        if (a == S) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        cout << "Среди этих элементов есть элемент, равный " << S << endl;
    }
    else {
        cout << "Среди этих элементов нет элемента, равного " << S << endl;
    }

    return 0;
}