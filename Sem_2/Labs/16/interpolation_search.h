#pragma once

int interpolation_search(int arr[], int left, int right, int key) {
    mid = left + (((key - arr[left]) + (right - left)) / (arr[right] - arr[left]));     // Определяем серединный индекс
    if (arr[mid] == key) {
        return mid;
    }
}