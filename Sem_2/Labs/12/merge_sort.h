#pragma once

void merge(int arr[], int left, int mid, int right) {
    int index1 = 0;
    int index2 = 0;
    int merged_array[right - left];

    while (left + index1 < mid && mid + index2 < right) {
        if (arr[left + index1] < arr[mid + index2]) {
            merged_array[index1 + index2] = arr[left + index1];
            index1++;
        }
        else {
            merged_array[index1 + index2] = arr[mid + index2];
            index2++;
        }
    }

    while (left + index1 < mid) {
        merged_array[index1 + index2] = arr[left + index1];
        index1++;
    }

    while (mid + index2 < right) {
        merged_array[index1 + index2] = arr[mid + index2];
        index2++;
    }

    for (int i = 0; i < index1 + index2; i++) {
        arr[left + i] = merged_array[i];
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left + 1 >= right) {
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid, right);
    merge(arr, left, mid, right);
}