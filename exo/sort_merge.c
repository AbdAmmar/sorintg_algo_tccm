#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Merge function to merge two halves of the array
void merge(int arr[], int left, int mid, int right) {

    // dim of left list
    int n1 = mid - left + 1;

    // dim of right list
    int n2 = right - mid;
    
    // Create temporary left array
    int* leftArr = (int*) malloc(n1 * sizeof(int));
    if (leftArr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Create temporary right array
    int* rightArr = (int*) malloc(n2 * sizeof(int));
    if (rightArr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    // Merge the temporary arrays back into the original array
    int i = 0, j = 0, k = left;

    // TODO
    //while ((i < ??) && (j < ??)) {

        // TODO
        //if (?? <= ??) {

            arr[k] = leftArr[i];
            i++;

        } else {

            arr[k] = rightArr[j];
            j++;

        }

        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    // TODO
    //while (?? < ??) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    leftArr = NULL;

    free(rightArr);
    rightArr = NULL;
}

// Merge Sort function that divides the array and calls the merge function
void mergeSort(int arr[], int left, int right) {

    /*
        A divide-and-conquer algorithm that divides the list 
        into equal halves, sorts each half, and then merges 
        the sorted halves.
    */

    // To stop recursion
    if (left >= right) return;

    // Find the middle point
    int mid = left + (right - left) / 2;
        
    // Recursively sort the two halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
        
    // Merge the two sorted halves
    merge(arr, left, mid, right);

}


int main() {

    int N = 15;

    // Allocates memory for an array of N integers
    int* arr = (int*) malloc(N * sizeof(int));
    if (arr == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed!\n");
        exit(1);  // Exit the program if memory allocation fails
    }

    // Generate random integers and fill the array
    generateRandomArray(arr, N, 100);

    // Print the unsorted array
    printf("Unsorted array: ");
    printArray(arr, N);

    // Sort the array
    mergeSort(arr, 0, N - 1);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, N);

    // Deallocate memory
    free(arr);
    arr = NULL;  // Set pointer to NULL after freeing memory

    return 0;
}

