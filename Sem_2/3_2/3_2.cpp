#include <iostream>
using namespace std;


int main() {
    int p, q, tmp;
    int lb = 20, ub = 100;
    int n = 50;
    int array[n];

    cin >> p >> q;

    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb; 
    }

    cout << "Массив до разворота: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    for (int i = 0; i <= (q - p) / 2; i++) {
        tmp = array[p + i];
        array[p + i] = array[q - i];
        array[q - i] = tmp;
    }

    cout << endl << "Массив после разворота: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    return 0;
}

