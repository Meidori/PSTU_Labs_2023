#include <iostream>
using namespace std;


void FillArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}


void ShowArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void DeleteElements(int *&arr, int &size, int K, int pos) {
    int *newNumbers = {new int[size - K]};
    for (int i = 0; i < pos - 1; i++) {
        newNumbers[i] = arr[i];
    }


    for (int i = pos - 1 + K; i < size; i++) {
        newNumbers[i - K] = arr[i];
    }
    size -= K;
    delete [] arr;
    arr = newNumbers;
}


void AddElements(int *&arr, int &size, int K, int pos) {
    int *newNumbers = {new int[size + K]};
    for (int i = 0; i < pos - 1; i++) {
        newNumbers[i] = arr[i];
    }
    
    int newNumber;
    cout << "Введите K новых чисел:" << endl;
    for (int i = pos - 1; i < pos - 1 + K; i++) {
        cin >> newNumber;
        newNumbers[i] = newNumber;
    }
    
    for (int i = pos - 1 + K; i < size + K; i++) {
        newNumbers[i] = arr[i - K];
    }

    size += K;
    delete [] arr;
    arr = newNumbers;
}


int main() {
    int n;
    cout << "Введите количество элементов в массиве:" << endl;
    cin >> n;
    int *numbers {new int[n]};
    FillArray(numbers, n);

    cout << "Массив до преобразований:" << endl;
    ShowArray(numbers, n);
    
    int K, pos1;
    cout << "Введите число K и номер, с какого элемента удалить K элементов:" << endl;
    cin >> K >> pos1;
    DeleteElements(numbers, n, K, pos1);

    cout << "Массив после удаления:" << endl;
    ShowArray(numbers, n);

    int pos2;
    cout << "Введите номер (ДЛЯ НОВГО МАССИВА), c какого элемента добавить K элементов:" << endl;
    cin >> pos2;
    AddElements(numbers, n, K, pos2);
    
    cout << "Массив после добавления:" << endl;
    ShowArray(numbers, n);

    delete [] numbers;
    numbers = nullptr; 

    return 0;
}