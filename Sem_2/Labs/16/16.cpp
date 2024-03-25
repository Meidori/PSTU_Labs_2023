#include <iostream>
#include "interpolation_search.h"
#include "lomuto_sort.h"
#include "linear_search.h"
#include "binary_search.h"
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

    cout << "Введите ключ: ";
    cin >> key;
    cout << endl;

    cout << "Выберите метод поиска:" << endl;
    cout << "1)Линейный\n2)Интерполяционный\n3)Бинарный" << endl;
    int search_number;
    cin >> search_number;

    switch (search_number) {
    case 1: {
        cout << "Введенный массив:" << endl;
        print_array(array_of_numbers, size);
        cout << "Первый индекс элемента массива равного ключу: " << linear_search(array_of_numbers, size, key) << endl;

        break;
    }
    case 2: {
        quick_lomuto(array_of_numbers, 0, size - 1);
        cout << "Массив после сортировки:" << endl;
        print_array(array_of_numbers, size);
        cout << "Первый индекс элемента массива равного ключу: " << interpolation_search(array_of_numbers, 0, size - 1, key) << endl;

        break;
    }
    case 3: {
        quick_lomuto(array_of_numbers, 0, size - 1);
        cout << "Массив после сортировки:" << endl;
        print_array(array_of_numbers, size - 1);
        cout << "Первый индекс элемента массива равного ключу: " << binary_search(array_of_numbers, 0, size - 1, key) << endl;
        break;
    }
    default:
        cout << "Ошибка!\n"; 
        break;
    }

    return 0;
}