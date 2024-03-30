#include <iostream>
#include "natural_sort.h"


const int SIZE = 25;


void print_array(int arr[], int size) {
    if (size > 0) {
        std::cout << arr[0];
    }
    for (int i = 1; i < size; i++) {
        std::cout << " " << arr[i];
    }
    std::cout << std::endl;
}


int main() {
    int array_of_numbers[SIZE] =  {56, 74, 95, 104, 13, 14, 1, 4, 7, 0, -1, 15, 34, 106, 23, 56, 17, 45, 76, 100, 34, 22, 25, 27, 75};

    std::cout << "Изначальный вид массива:" << std::endl;
    print_array(array_of_numbers, SIZE);

    sort_series(array_of_numbers, SIZE);

    std::cout << "Вид массива после сортировки:" << std::endl;
    print_array(array_of_numbers, SIZE);

    return 0;
}