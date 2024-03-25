#pragma once

void counting_sort(int *arr, int size) {
    int *sorted_array = new int[size];

    int max = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int *count;
    count = new int[max + 1];

    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {     // подсчёт
        count[arr[i]]++;
    }

    for (int i = 0; i <= max; i++) {     // вычисление префиксных сумм
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        sorted_array[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = sorted_array[i];
    }

    delete[] count;
    delete[] sorted_array;
}