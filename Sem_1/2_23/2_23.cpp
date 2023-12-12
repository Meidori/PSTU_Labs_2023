#include <iostream>
#include <cmath>
using namespace std;


int main() {
    float N, max = -2, a;
    int counter = 0;
    cin >> N;

    for (int i = 1; i <= N; i++) {          // ищем максимальный элемент
        a = sin(N + (i / N));

        if (a > max) {
            max = a;
        }
    }
    
    for (int i = 1; i <= N; i++) {
        a = sin(N + (i / N));

        if (a == max) {
            counter += 1;
        }
    }

    cout << counter << endl;
    return 0;
}