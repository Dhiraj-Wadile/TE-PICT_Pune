#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int size, int key) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Key found
        }

        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Key not found
}

int main(int argc, char *argv[]) {
    int a[100];
    int n;

    printf("\nEnter the number to find in the array: ");
    scanf("%d", &n);

    for (int i = 0; i < argc; i++) {
        a[i] = atoi(argv[i]);
    }

    // Sort the array before performing binary search
    int size = argc;
    int key = n;

    int result = binarySearch(a, size, key);

    if (result != -1) {
        printf("\nEntered number is found in the array at index %d", result);
    } else {
        printf("\nEntered number is not in the array");
    }

    return 0;
}

