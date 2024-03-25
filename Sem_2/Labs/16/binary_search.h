#pragma once

int binary_search(int arr[], int left, int right, int key) {
    int mid = (right + left) / 2;
    if (arr[mid] > key) {
        binary_search(arr, left, mid - 1, key);
    }
    else if (arr[mid] < key) {
        binary_search(arr, mid + 1, right, key);
    }
    else {
        return mid;
    }
}