#include <iostream>
using namespace std;


int main() {
    int tmp, n = 10;
    int lb = 20, ub = 100;
    int array[n * 2];

    
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb;
    }

    for (int i = n; i < n * 2; i++) {
        array[i] = 0;
    }

    cout << "Массив до преобразования: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    for (int i = 0; i < n; i++) {
        if (array[i] % 2 == 0) {
            for (int j = n - 1; j >= i; j--) {
                array[j + 1] = array[j];
            }
            array[i] = -1;
            i++;
            n++;
        }
    }

    cout << endl << "Массив после преобразования: " << endl;
    
    for (int i = 0; i < n * 2; i++) {
        cout << array[i] << " ";
    }

    return 0;    

}