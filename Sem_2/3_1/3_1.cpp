#include <iostream>
using namespace std;


int main() {
    int tmp;
    int lb = 20, ub = 100;
    int n = 50;
    int array[n];

    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb; 
    }

    cout << "Массив до разворота: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    for (int i = 0; i < n / 2; i++) {
        tmp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = tmp; 
    }   

    cout << endl << "Массив после разворота: " << endl;

    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }

    return 0;
}