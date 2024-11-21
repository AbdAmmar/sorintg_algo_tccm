#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Helper function to perform MSD (Most Significant Digit) radix sort recursively
void msdRadixSort(int arr[], int n, int exp) {

    // if the array size is less than 2 or all bits are processed, stop recursion
    if (n < 2 || exp < 0) return;

    // Temporary arrays to store the elements for 0 and 1 bits
    int* tmp[2];
    tmp[0] = (int*) malloc(n * 2 * sizeof(int)); // Allocate memory for both arrays in one go
    tmp[1] = tmp[0] + n; // Second array starts after the first

    if (tmp[0] == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Since the base is 2, we need a count array of size 2 to count 0s and 1s
    int count[2] = {0};

    // Create a mask by shifting 1 to the left by 'exp' positions
    // TODO: Set the correct mask for the current bit
    int mask = ??

    // Distribute elements into tmp[0] (for bit 0) and tmp[1] (for bit 1)
    for (int i = 0; i < n; i++) {

        // Determine if the bit at position 'exp' is 0 or 1
        int exp_bit = 0;
        if ((arr[i] & mask) != 0) {
            exp_bit = 1;
        }

        // Add arr[i] to the corresponding tmp array
        tmp[exp_bit][count[exp_bit]] = arr[i];
        count[exp_bit]++;
    }

    // Recursively sort the tmp[0] array based on the next significant bit
    // TODO: Replace ?? with the correct size
    msdRadixSort(tmp[0], ??, exp - 1);

    // Recursively sort the tmp[1] array based on the next significant bit
    // TODO: Replace ?? with the correct size
    msdRadixSort(tmp[1], ??, exp - 1);

    // Copy the sorted elements from tmp arrays back to the original array
    for (int i = 0; i < count[0]; i++) {
        arr[i] = tmp[0][i];
    }
    for (int i = count[0]; i < n; i++) {
        arr[i] = tmp[1][i-count[0]];
    }

    // Free the allocated memory for tmp arrays
    free(tmp[0]);
    tmp[0] = NULL;
}


// Radix Sort function
void radixSort(int arr[], int n) {

    /*
        Non-comparative integer sorting algorithm that sorts by 
        processing individual digits. It works by sorting the numbers 
        bit by bit starting from the most significant bit (MSD) to 
        the least significant bit (LSD).
    */

    // Find the maximum number of bits in the largest number
    int maxBits = getMaxBits(arr, n);

    // Perform MSD radix sort starting from the most significant bit
    msdRadixSort(arr, n, maxBits - 1); // maxBits - 1 for 0-based bit indexing

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
    generateRandomArray(arr, N, 1000);

    // Print the unsorted array
    printf("Unsorted array: ");
    printArray(arr, N);

    // Sort the array
    radixSort(arr, N);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, N);

    // Deallocate memory
    free(arr);
    arr = NULL;  // Set pointer to NULL after freeing memory

    return 0;
}

