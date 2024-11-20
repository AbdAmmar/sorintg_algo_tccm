#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "utils.h"

// Function to sort the array using Bubble Sort
void bubbleSort(int arr[], int n) {

    /* 
        A simple comparison-based algorithm. It repeatedly 
        steps through the list, compares adjacent elements, 
        and swaps them if they are in the wrong order.
    */

    for (int i = 0; i < n - 1; i++) {

        // Assume the array is sorted before the inner loop
        bool is_sorted = true;

        // TODO
        //for (int j = ??; j < ??; j++) {

            // Swap if need

            // TODO
            //if (?? > ??) {

                // TODO
                //swap(arr, ??, ??);

                // we did some swap, so we aren't done yet
                is_sorted = false;
            }
        }

        if (is_sorted) return;
    }

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
    bubbleSort(arr, N);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, N);

    // Deallocate memory
    free(arr);
    arr = NULL;  // Set pointer to NULL after freeing memory

    return 0;
}

