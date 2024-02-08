#include <iostream>
using namespace std;

int main() {
    int n = 50;
    int max = 0, min = 101;
    int lb = 20, ub = 100;
    int array[n];

    
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb;
    }

    for (int i = 0; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }

    cout << "Максимальный элемент последовательности: " << max << endl;
    cout << "Минимальный элемент последовательности: " << min << endl;

    return 0;
}