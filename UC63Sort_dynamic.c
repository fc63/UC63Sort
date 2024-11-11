#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    int count;
} HashNode;

typedef struct {
    HashNode* table;
    int size;
    int uniqueSize;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->table = (HashNode*)calloc(size, sizeof(HashNode));
    hashTable->size = size;
    hashTable->uniqueSize = 0;
    return hashTable;
}

void freeHashTable(HashTable* hashTable) {
    if (hashTable) {
        free(hashTable->table);
        free(hashTable);
    }
}

void insert(HashTable* hashTable, int value) {
    int index = abs(value) % hashTable->size;
    while (hashTable->table[index].count != 0 && hashTable->table[index].value != value) {
        index = (index + 1) % hashTable->size;
    }
    if (hashTable->table[index].count == 0) {
        hashTable->table[index].value = value;
        hashTable->uniqueSize++;
    }
    hashTable->table[index].count++;
}

void extractUniqueAndCounts(HashTable* hashTable, int** uniqueArr, int** countArr) {
    *uniqueArr = (int*)malloc(hashTable->uniqueSize * sizeof(int));
    *countArr = (int*)malloc(hashTable->uniqueSize * sizeof(int));
    int pos = 0;
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i].count > 0) {
            (*uniqueArr)[pos] = hashTable->table[i].value;
            (*countArr)[pos] = hashTable->table[i].count;
            pos++;
        }
    }
}

// Dynamic run determination based on array size.
int calculateRun(int size) {
    if (size <= 16) {
        return 4;
    } else if (size <= 32) {
        return 8;
    } else if (size <= 64) {
        return 16;
    } else if (size <= 1024) {
        return 32;
    } else {
        return 64;
    }
}

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
    int run = calculateRun(n);

    for (int i = 0; i < n; i += run) {
        insertionSort(arr, i, (i + run - 1 < n - 1) ? i + run - 1 : n - 1);
    }

    for (int size = run; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;

            if (mid < right) merge(arr, left, mid, right);
        }
    }
}

void reconstructArray(int* arr, int* uniqueArr, int* countArr, int uniqueSize) {
    int pos = 0;
    for (int i = 0; i < uniqueSize; i++) {
        int value = uniqueArr[i];
        int count = countArr[i];
        for (int j = 0; j < count; j++) {
            arr[pos++] = value;
        }
    }
}

void UC63Sort(int* arr, int size) {
    HashTable* hashTable = createHashTable(size * 2);

    for (int i = 0; i < size; i++) {
        insert(hashTable, arr[i]);
    }

    int* uniqueArr;
    int* countArr;
    extractUniqueAndCounts(hashTable, &uniqueArr, &countArr);

    sortUniqueArray(uniqueArr, hashTable->uniqueSize);

    reconstructArray(arr, uniqueArr, countArr, hashTable->uniqueSize);

    free(uniqueArr);
    free(countArr);
    freeHashTable(hashTable);
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
