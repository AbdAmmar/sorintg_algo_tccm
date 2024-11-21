#include <stdio.h>
#include "utils.h"


// Function to partition the array for Quick Sort
int partition(int arr[], int left, int right) {

    /*
        This function takes the last element as pivot, places
        the pivot element at its correct position in the sorted 
        array, and places all smaller (smaller than pivot) to 
        left of pivot and all greater elements to right of pivot.
    */

    // Choose the last element as pivot
    // TODO: Replace ?? with the index of the pivot element
    int pivot = arr[??];

    // Index of the smaller element, initially set to one less than the starting index
    int i = left - 1;

    // Loop through the array from the 'left' index to 'right - 1'
    for (int j = left; j < right; j++) {

        // If the current element is smaller than or equal to the pivot
        // TODO: Replace ?? with the correct comparison element
        if (arr[??] <= pivot) {

            // Increment the index of the smaller element
            i++;

            // Swap the current element with the element at index 'i'
            swap(arr, i, j);
        }
    }

    // Swap the pivot element with the element at index 'i + 1' to place it at the correct position
    // TODO: Replace ?? with the correct index of the pivot element
    swap(arr, i + 1, ??);

    // Return the partition index
    return i + 1;
}


// Quick Sort function that recursively sorts the array
void quickSort(int arr[], int left, int right) {

    /*
        A divide-and-conquer algorithm that selects a 'pivot' element 
        from the array and partitions the other elements into two sub-arrays, 
        according to whether they are less than or greater than the pivot.
    */

    // To stop recursion
    if (left >= right) return;

    // Partition the array
    int pi = partition(arr, left, right);

    // Recursively sort the two halves
    quickSort(arr, left, pi - 1);
    quickSort(arr, pi + 1, right);

}


int main() {

    int N = 15;

    // Create an array of size N
    int arr[N];

    // Generate random integers and fill the array
    generateRandomArray(arr, N, 100);

    // Print the unsorted array
    printf("Unsorted array: ");
    printArray(arr, N);

    // Sort the array
    quickSort(arr, 0, N - 1);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, N);

    return 0;
}

