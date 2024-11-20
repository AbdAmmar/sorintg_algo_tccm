#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Helper function to perform MSD radix sort recursively
void msdRadixSort(int arr[], int n, int exp) {

    // To stop recursion
    if (n < 2 || exp < 0) return;

    // Temporary array to store elements
    int* tmp[2];
    tmp[0] = (int*) malloc(n*2 * sizeof(int));
    tmp[1] = tmp[0] + n;

    if (tmp[0] == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // since base is 2, we need a count array of size 2
    int count[2] = {0};

    // create a mask by shifting 1 to the left by (exp-1) positions
    // TODO
    // int mask = ?? 

    // append arr elements to tmp[0] or tmp[1]
    for (int i = 0; i < n; i++) {

        // Determine if first bit is 0 or 1
        int first_bit = 0;
        if ((arr[i] & mask) != 0) {
          first_bit = 1;
        }

        // add arr[i] in tmp[0] array or tmp[1] array
        tmp[first_bit][count[first_bit]] = arr[i];
        count[first_bit]++;
    }

    // Sort tmp[0] array according to the next bit
    // TODO
    //msdRadixSort(tmp[0], ??, exp-1);

    // Sort tmp[1] array according to the next bit
    // TODO
    //msdRadixSort(tmp[1], ??, exp-1);

    // Copy the sorted numbers into the original array
    for (int i = 0; i < count[0]; i++) {
        arr[i] = tmp[0][i];
    }
    for (int i = count[0]; i < n; i++) {
        arr[i] = tmp[1][i-count[0]];
    }

    free(tmp[0]);
    tmp[0] = NULL;
}


// Radix Sort function
void radixSort(int arr[], int n) {

    /*
        Non-comparative integer sorting algorithm that sorts by 
        processing individual digits. It works by sorting the numbers 
        bit by bit starting from the most significant bit to 
        the least significant bit.
    */

    // Find the maximum number of bits in the largest number
    int maxBits = getMaxBits(arr, n);

    // Function to perform MSD radix sort
    msdRadixSort(arr, n, maxBits);

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

