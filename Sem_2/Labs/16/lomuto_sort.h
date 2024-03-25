#pragma once

int partition(int arr[], int left, int right) {
    int tmp;
    int pivot = arr[right];
    int index = left - 1;

    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            index++;
            tmp = arr[index];
            arr[index] = arr[i];
            arr[i] = tmp;
        }
    }
    tmp = arr[index + 1];
    arr[index + 1] = arr[right];
    arr[right] = tmp;
    return (index + 1);
}


void quick_lomuto(int arr[], int left, int right) {
    if (left < right) {
        int index = partition(arr, left, right);
        quick_lomuto(arr, left, index - 1);
        quick_lomuto(arr, index + 1, right);
    }
}