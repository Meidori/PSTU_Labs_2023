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
    int array_of_numbers[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array_of_numbers[i] = 1 + rand() % 100;
    }
    array_of_numbers[24] = -1;

    std::cout << "Изначальный вид массива:" << std::endl;
    print_array(array_of_numbers, SIZE);

    natural_sort(array_of_numbers, SIZE);

    std::cout << "Вид массива после сортировки:" << std::endl;
    print_array(array_of_numbers, SIZE);

    return 0;
}