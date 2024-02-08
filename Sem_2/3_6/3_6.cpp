#include <iostream>
using namespace std;


int main() {
    int n = 50;
    int max = 0, cnt = 0;
    int lb = 20, ub = 100;
    int array[n];
    
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb;
    }

    for (int i = 0; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (array[i] == max) {
            cnt++;
        }
    }

    cout << "Максимальный элемент последовательности: " << max << endl;
    cout << "Этот элемент встречается: " << cnt << " раз(а)." << endl;

    return 0;
}