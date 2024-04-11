#pragma once


void merge(int merged[], int arr1[], int arr2[], int size1, int size2) {
    int i = 0, j = 0, index = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            merged[index++] = arr1[i++];
        }
        else {
            merged[index++] = arr2[j++];
        }
    }

    while (i < size1) {
        merged[index++] = arr1[i++];
    }

    while (j < size2) {
        merged[index++] = arr2[j++];
    }
}


void sort_series(int arr[], int size, int array_of_sizes[], int number_of_series, int array_index, int current_series) {
    if (current_series + 1 >= number_of_series) {
        current_series = 0;
        array_index = 0;
    }

    int memorize_index = array_index;
    
    int tmp_arr1[array_of_sizes[current_series]];
    for (int i = 0; i < array_of_sizes[current_series]; i++) {
        tmp_arr1[i] = arr[array_index++];
    }
    current_series++;

    int tmp_arr2[array_of_sizes[current_series]];
    for (int i = 0; i < array_of_sizes[current_series]; i++) {
        tmp_arr2[i] = arr[array_index++];
    }

    int tmp_merged[array_of_sizes[current_series] + array_of_sizes[current_series - 1]];
    merge(tmp_merged, tmp_arr1, tmp_arr2, array_of_sizes[current_series - 1], array_of_sizes[current_series]);

    array_index = memorize_index;
    for (int i = 0; i < array_of_sizes[current_series] + array_of_sizes[current_series - 1]; i++) {
        arr[array_index++] = tmp_merged[i];
    }
    
    int tmp = array_of_sizes[current_series - 1];
    array_of_sizes[current_series - 1] = tmp + array_of_sizes[current_series];
    for (int i = current_series; i < number_of_series - 1; i++) {
        array_of_sizes[i] = array_of_sizes[i + 1];
    }
    array_of_sizes[number_of_series - 1] = 0;
    number_of_series--;

    if (number_of_series > 1) {
        sort_series(arr, size, array_of_sizes, number_of_series, array_index, current_series);
    }
}


void merge_sort(int arr[], int size) {
    int array_of_sizes[size];
    for (int i = 0; i < size; i++) {
        array_of_sizes[i] = 1;
    }
    int number_of_series = size;
    int array_index = 0;
    int current_series = 0;
    sort_series(arr, size, array_of_sizes, number_of_series, array_index, current_series);
}

