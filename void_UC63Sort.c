#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RUN 63

typedef struct {
    int* uniqueArr;
    int* countArr;
    int uniqueSize;
    int max;
} UniqueData;

void insertionSort(int* arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(int* arr, int left, int mid, int right) {
    int len1 = mid - left + 1, len2 = right - mid;
    int* leftArr = (int*)malloc(len1 * sizeof(int));
    int* rightArr = (int*)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++) leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < len1) arr[k++] = leftArr[i++];
    while (j < len2) arr[k++] = rightArr[j++];

    free(leftArr);
    free(rightArr);
}

void sortUniqueArray(int* arr, int n) {
    for (int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, (i + RUN - 1 < n - 1) ? i + RUN - 1 : n - 1);
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if (mid < right) merge(arr, left, mid, right);
        }
    }
}

void UC63Sort(int* arr, int size) {
    UniqueData data;
    data.max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > data.max) data.max = arr[i];
    }

    data.uniqueArr = (int*)malloc(size * sizeof(int));
    data.countArr = (int*)calloc(data.max + 1, sizeof(int));
    data.uniqueSize = 0;

    bool* isUnique = (bool*)calloc(data.max + 1, sizeof(bool));
    for (int i = 0; i < size; i++) {
        if (!isUnique[arr[i]]) {
            isUnique[arr[i]] = true;
            data.uniqueArr[data.uniqueSize++] = arr[i];
        }
        data.countArr[arr[i]]++;
    }
    free(isUnique);

    sortUniqueArray(data.uniqueArr, data.uniqueSize);

    int pos = 0;
    for (int i = 0; i < data.uniqueSize; i++) {
        int value = data.uniqueArr[i];
        int count = data.countArr[value];
        for (int j = 0; j < count; j++) {
            arr[pos++] = value;
        }
    }

    free(data.uniqueArr);
    free(data.countArr);
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {63, 3, 12, 1, 5, 5, 3, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    UC63Sort(arr, size);

    printf("Sorted Array: ");
    printArray(arr, size);

    return 0;
}
