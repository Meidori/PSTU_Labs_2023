#include <iostream>
using namespace std;

// Лабораторная работа № 5, вариант 5
const int n = 3;    // размер квадратной матрицы

/* Функция для вычисления значения элемента a[line + 1][column + 1] в матрице, 
полученной путем умножения данной матрицы (matrix[n][n]) на данную транспонированную матрицу:*/
int multiplication(int matrix[n][n], int line, int column) {    
    int s = 0;
    for (int i = 0; i < n; i++) {
        s += (matrix[line][i] * matrix[column][i]);
    }
    return s;
}


int main() {
    int matrix[n][n];
    int el;
    bool flag = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10;     // заполняем массив (матрицу) случайными ЦЕЛЫМИ числами от 0 до 9  
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {       // проверяем находится ли элемент на главной диагонали
                el = multiplication(matrix, i, j);
                if (el != 1) {
                    flag = 0;
                }
            }
            else {
                el = multiplication(matrix, i, j);
                if (el != 0) {
                    flag = 0;
                }
            }
        }
    }

    cout << "Матрица: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;     
    }
    if (flag) {
        cout << "Является ортонормированной" << endl;
    }
    else {
        cout << "Не является ортонормированной" << endl;
    }

    return 0;
}