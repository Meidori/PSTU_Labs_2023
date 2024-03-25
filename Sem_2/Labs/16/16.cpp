#include <iostream>
#include "interpolation_search.h"
#include "lomuto_sort.h"
using namespace std;


void print_array(int arr[], int size) {
    if (size != 0) {
        cout << arr[0];
    }
    for (int i = 1; i < size; i++) {
        cout << " " << arr[i];
    }
    cout << endl;
}


int main() {
    int size, key, tmp;
    cout << "Введите размер массива целых чисел." << endl;
    cin >> size;
    int array_of_numbers[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите элемент - целое число: ";
        cin >> tmp;
        array_of_numbers[i] = tmp;
        cout << endl;
    }

    quick_lomuto(array_of_numbers, 0, size - 1);
    cout << "Массив после сортировки:" << endl;
    print_array(array_of_numbers, size);

    cout << "Введите ключ: ";
    cin >> key;
    cout << endl;
    cout << "Первый индекс элемента массива равного ключу: " << interpolation_search(array_of_numbers, 0, size - 1, key) << endl;

    return 0;
}