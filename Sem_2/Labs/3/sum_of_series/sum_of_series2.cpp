#include <iostream>
#include <cmath>
using namespace std;


int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}


int main() {
    int n, x;
    float sum = 0;
    cin >> n;
    cin >> x;

    for (int i = 0; i < n; i++) {
        sum += pow(x, i) / factorial(i);
    }
    
    cout << sum << endl;
    return 0;
}