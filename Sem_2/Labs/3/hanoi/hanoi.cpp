#include <iostream>
using namespace std;


void hanoi(int n, int start, int end, int other) {
    if (n != 0) {
        hanoi(n - 1, start, other, end);

        cout << start << " -> " << end << endl;

        hanoi(n - 1, other, end, start);      
    }
}


int main() {
    int n, first, last;
    cout << "Введите количество дисков: " << endl;
    cin >> n;

    cout << "Введите начальную башню: " << endl;
    cin >> first;
    cout << "Введите конечную башню: " << endl;
    cin >> last;

    int other = 6 - (first + last);

    hanoi(n, first, last, other);
}


