#include <iostream>
using namespace std;

int main() {
    int n, temp, max = -10000, min = 10000;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> temp;
        if (temp < min) {
            min = temp;
        }
        
        if (temp > max) {
            max = temp;
        }
    }

    cout << max + min << endl;
    return 0;
}