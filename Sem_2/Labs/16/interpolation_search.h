#pragma once

int interpolation_search(int arr[], int left, int right, int key) {
    int mid = left + (((key - arr[left]) + (right - left)) / (arr[right] - arr[left]));     // Определяем серединный индекс
    if (arr[mid] < key) {
        interpolation_search(arr, mid + 1, right, key);
    }
    else if (arr[mid] > key) {
        interpolation_search(arr, left, mid - 1, key);
    }
    else {
        return mid;
    }
}


