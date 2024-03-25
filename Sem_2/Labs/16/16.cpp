#include <iostream>
#include "interpolation_search.h"
#include 
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
    int size, tmp;
    cout << "Введите размер массива целых чисел." << endl;
    cin >> size;
    int array_of_numbers[size];
    for (int i = 0; i < size; i++) {
        cout << "Введите элемент - целое число: ";
        cin >> tmp;
        array_of_numbers[i] = tmp;
        cout << endl;
    }
    


    



}