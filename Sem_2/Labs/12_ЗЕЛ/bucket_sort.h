#pragma once

void bucket_sort(double *arr, int size) {  
    const int BUCKET_NUM = 10;
    const int BUCKET_SIZE = 10;

    double buckets[BUCKET_NUM][BUCKET_SIZE];
    int bucket_sizes[BUCKET_NUM]{0};

    for (int i = 0; i < size; i++) {
        int bucket_index = static_cast<int>(arr[i] / BUCKET_NUM);
        buckets[bucket_index][bucket_sizes[bucket_index]] = arr[i];
        bucket_sizes[bucket_index]++;
    }

    for (int i = 0; i < BUCKET_NUM; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            double tmp = buckets[i][j];
            int k = j - 1;
            while (k >= 0 && buckets[i][k] > tmp) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = tmp;
        }
    }

    int index = 0;
    for (int i = 0; i < BUCKET_NUM; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
}