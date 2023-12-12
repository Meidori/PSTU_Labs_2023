#include <iostream>
#include <cmath>
using namespace std;


int main() {
    float a, N, max = -2;
    int pos;
    cin >> N;
    
    for (int i = 1; i <= N; i++) {
        a = sin(N + (i / N));

        if (a > max) {
            pos = i;
            max = a;
        }
    }

    cout << "Номер: " << pos << " Максимальное: " << max << endl;
    return 0;
}