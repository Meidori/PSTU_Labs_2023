#include <iostream>
#include "bucket_sort.h"
#include "counting_sort.h"
#include "merge_sort.h"
#include "lomuto_sort.h"
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
        /*Блочная сортировка, также известная как сортировка корзин или bucket sort, эффективно работает на массивах с равномерным распределением элементов в заданном диапазоне. 
        Этот алгоритм работает лучше всего, когда элементы равномерно распределены по различным интервалам значений. Это позволяет создать корзины (или блоки), которые содержат 
        сравнительно одинаковое количество элементов и поэтому требуют относительно меньше времени на сортировку. 
        Блочная сортировка может быть менее эффективной, если данные имеют неравномерное распределение или если диапазон значений очень велик по сравнению с количеством элементов в массиве, 
        в таких случаях потребуется больше памяти.*/
        double array_of_nums[size] = {2.4, 2.7, 1.4, 5.4, 8.2, 9.1, 1.2, 1.9, 3.2, 6.6, 6.6, 2.43, 9.23, 3.33, 3.4, 3.2, 5.3, 8.42, 1.123, 4.32, 5.3, 6.0, 7.0, 2.32, 3.0};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        bucket_sort(array_of_nums, size);
        cout << "Отсортированный массив:" << endl;
        print_array(array_of_nums, size);
        break;
    }
    case 2: {
        /*Сортировка подсчётом (counting sort) эффективна для массивов с относительно небольшим диапазоном значений. Этот алгоритм сортировки подходит для 
        ситуаций, когда известен диапазон элементов, и он работает за линейное время относительно размера входного массива. 
        Таким образом, сортировка подсчётом может быть выгодной для массивов, в которых значения находятся в ограниченном диапазоне, 
        а также для ситуаций, когда время выполнения является критическим.*/
        int array_of_nums[size] = {15, 15, 15, 15, 3, 5, 5, 5, 3, 3, 5, 3, 9, 7, 7, 9, 9, 9, 7, 3, 15, 4, 4, 3, 6};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        counting_sort(array_of_nums, size);
        cout << "Отсортированный массив:" << endl;
        print_array(array_of_nums, size);
        break;
    }
    case 3: {
        /*Сортировка слиянием эффективнее всего работает на массивах, которые содержат большое количество элементов и требуют стабильной
        и эффективной сортировки. Это значит, что сортировка слиянием обычно применяется для сортировки больших массивов, 
        которые могут не соответствовать критериям частичной отсортированности, используемым в других алгоритмах, таких как сортировка Шелла. 
        Сортировка слиянием также эффективна на массивах, которые могут содержать дубликаты или элементы с одинаковыми значениями.*/
        int array_of_nums[size] = {23, 25, 64, 32, 21, 53, 97, 34, 64, 98, 43, 32, 24, 53, 26, 98, 23, 51, 42, 99, 23, 12, 23, 10, 99};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        merge_sort(array_of_nums, 0, size - 1);
        cout << "Отсортированный массив:" << endl;
        print_array(array_of_nums, size);
        break;
    }
    case 4: {
        /*Схема Ломуто - это один из методов быстрой сортировки (quicksort), и она обычно используется для сортировки произвольно перемешанных массивов. 
        Она хорошо работает как на массивах с большим числом повторяющихся элементов, так и на массивах без повторений. Работает эффективно как на упорядоченных, 
        так и на случайно перемешанных массивах. Схема Ломуто хорошо справляется с различными видами входных данных и обычно предпочтительна в случае, 
        когда нет необходимости в дополнительной оптимизации под конкретный тип данных.*/
        int array_of_nums[size] = {163, 344, 426, 136, 984, 852, 413, 642, 238, 923, 98, 106, 301, 519, 129, 231, 539, 1476, 259, 616, 259, 149, 931, 346, 100};
        cout << "Изначальный массив:" << endl;
        print_array(array_of_nums, size);
        quick_lomuto(array_of_nums, 0, size - 1);
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