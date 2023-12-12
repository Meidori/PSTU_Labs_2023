#include <iostream>
#include <cmath>
using namespace std;


int main() {
    float N, x, factorial = 1, y = 0;
    cin >> N;
    cin >> x;
    for (int i = 0; i <= N; i++) {
        if (i != 0) {
            factorial = factorial * i;
        }  
        y += pow(x, i) / factorial;    
    }

    cout << y << endl;
    return 0;
} 