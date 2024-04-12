#pragma once


int partition(int arr[], int left, int right) {
    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (true) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            return j;
        }
        std::swap(arr[i++], arr[j--]);
    }
}


void qsort(int arr[], int left, int right) { 
    if (left < right) {
        int pivot_index = partition(arr, left, right);
        qsort(arr, left, pivot_index);
        qsort(arr, pivot_index + 1, right);
    }
}