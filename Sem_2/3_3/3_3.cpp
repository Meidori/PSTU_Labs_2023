#include <iostream>
using namespace std;


int main() {
    int lb = 20, ub = 100;
    int n = 50;
    int k, tmp;
    int array[n];

    cin >> k;

    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb; 
    }

    cout << "Массив до преобразования: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    for (int i = 0; i < k; i++) {
        tmp = array[n - 1];
        for (int j = n - 1; j > 0; j--) {
            array[j] = array[j - 1];
        }
        array[0] = tmp;
    }

    cout << endl << "Массив после преобразования: " << endl;
    
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    return 0;
}