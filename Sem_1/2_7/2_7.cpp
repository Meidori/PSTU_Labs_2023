#include <iostream>
#include <cmath>
using namespace std;


void taskA(int N) {
    if (pow(sqrt(N), 2) == N and N > 0) {
        for (int i = 1; i <= sqrt(N); i++) {
            for (int j = 1; j <= sqrt(N); j++) {
                cout << "*"; 
            }
            cout << "\n";
        }
    }

    else {
        cout << "Заданное число N не подходит для реализации условия А. N должно быть полным квадратом." << endl;
    }
}


void taskB(int N) {
    if (N >= 2) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cout << "*";
            }
            cout << "\n";
        }
    }

    else {
        cout << "Заданное число N не подходит для реализации условия Б. N должно быть больше или равно 2." << endl;
    }
}


void taskC(int N) {
    int spaces = N - 2;

    if (N >= 3) {
        for (int i = 1; i <= N; i++) {
            cout << "*";
        }
        cout << "\n";

        for (int i = 1; i <= N - 2; i++) {
            cout << "*";
            for (int j = 1; j <= spaces; j++) {
                cout << " ";
            }
            cout << "*";
            cout << "\n";
        }

        for (int i = 1; i <= N; i++) {
            cout << "*";
        }
    }
    
    else {
        cout << "Заданное число N не подходит для реализации условия В. N должно быть больше или равно 3." << endl;
    }
}


int main() {
    int N;
    cin >> N;

    cout << "Результат для задания А:" << endl;
    taskA(N);

    cout << "Результат для задания Б:" << endl;
    taskB(N);

    cout << "Результат для задания В:" << endl;
    taskC(N);

    return 0;
}
