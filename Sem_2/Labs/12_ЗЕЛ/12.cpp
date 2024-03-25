#include <iostream>
#include "bucket_sort.h"
#include "counting_sort.h"
using namespace std;


template<typename T>
void print_array(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    int size = 25;
    cout << "Выберите сортировку:\n1)Блочная\n2)Подсчетом\n3)Слиянием\n4)Быстрая по Ломуто\n";
    int sort_number;
    cin >> sort_number;

    switch (sort_number) {
    case 1: {
        double array_of_nums[size] = {2.4, 2.7, 1.4, 5.4, 8.2, 9.1, 1.2, 1.9, 3.2, 6.6, 6.6, 2.43, 9.23, 3.33, 3.4, 3.2, 5.3, 8.42, 1.123, 4.32, 5.3, 6.0, 7.0, 2.32, 3.0};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        bucket_sort(array_of_nums, size);
        cout << "Отсортированный массив:" << endl;
        print_array(array_of_nums, size);
        break;
        }
    case 2: {
        int array_of_nums[size] = {15, 15, 15, 15, 3, 5, 5, 5, 3, 3, 5, 3, 9, 7, 7, 9, 9, 9, 7, 3, 15, 4, 4, 3, 6};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        counting_sort(array_of_nums, size);
        cout << "Отсортированный массив:" << endl;
        print_array(array_of_nums, size);
        break;
        }
    default: {
        cout << "Ошибка!\n";
        break;
        }
    }
    return 0;
}