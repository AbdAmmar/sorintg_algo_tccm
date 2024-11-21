#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "struct.h"

// Function to generate random integers between 0 and range - 1
void generateRandomArray(int arr[], int n, int range) {

    // Seed the random number generator with the current time
    // This ensures that we get different sequences of random numbers on each run
    srand(time(0));

    // Loop through the array to fill it with random numbers
    for (int i = 0; i < n; i++) {
        // Generate a random integer between 0 and range - 1
        // The modulo operator ensures the number is within the desired range
        arr[i] = rand() % range;
    }
}

// Function to print the array
void printArray(int arr[], int n) {

    // Loop through the array elements
    for (int i = 0; i < n; i++) {
        // Print each element followed by a space
        printf("%d ", arr[i]);
    }
    // Print a newline character after printing all elements to move to the next line
    printf("\n");
}

// Function to swap two elements in the array
void swap(int arr[], int i, int j) {
    // Store the value at index i in a temporary variable
    int temp = arr[i];
    
    // Assign the value at index j to index i
    arr[i] = arr[j];
    
    // Assign the value stored in the temporary variable to index j
    arr[j] = temp;
}


// Function to get the maximum value in the array
int getMax(int arr[], int n) {

    // Initialize the maximum value with the first element of the array
    int max = arr[0];

    // Loop through the array starting from the second element
    for (int i = 1; i < n; i++) {
        // If the current element is greater than the current maximum, update the maximum
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Return the maximum value found in the array
    return max;
}



// Function to get the maximum number of bits required to represent the largest number in the array
int getMaxBits(int arr[], int n) {

    // Initialize the maximum value with the first element of the array
    int max = arr[0];

    // Loop through the array to find the maximum value
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Initialize the count of bits to 0
    int maxBits = 0;

    // Loop to count the number of bits required to represent the maximum value
    while (max > 0) {
        maxBits++;     // Increment the bit count
        max >>= 1;     // Right shift the maximum value by 1 bit (equivalent to dividing by 2)
    }

    // Return the number of bits required to represent the maximum value
    return maxBits;
}


// Function to generate a random integer with a fixed number of 1 bits
int generateDeterminantWithKOnes(int numBits, int k) {

    // Initialize the determinant to 0
    int det = 0;

    // Create an array to hold all bit positions
    int positions[numBits];
    for (int i = 0; i < numBits; i++) {
        positions[i] = i;
    }

    // Seed the random number generator with the current time plus a random value
    // This ensures a different seed on each run and further randomization
    srand(time(NULL) + rand());

    // Randomly select k positions to set to 1
    for (int i = 0; i < k; i++) {
        // Select a random position from the remaining positions
        int j = i + rand() % (numBits - i);

        // Swap the selected position with the current position to "remove" it from the pool
        int temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;

        // Set the bit at the chosen position
        det |= (1 << positions[i]);
    }

    // Ensure the result is positive by masking out the sign bit (if numBits is equal to the number of bits in an int)
    if (det < 0) {
        det &= (1 << (numBits - 1)) - 1;  // Mask the sign bit if it is set
    }

    return det;
}


// Function to initialize the wavefunction in a random way
void initializePsiTable(Psi* psi, int n, int k) {

    // Number of bits in an integer
    int numBits = sizeof(int) * 8;

    // Variable to hold the sum of the squares of the coefficients for normalization
    double psi_norm = 0.0;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate random positive integers for determinants and random doubles for coefficients
    for (int i = 0; i < n; i++) {

        // Variable to store the temporary determinant
        int det_tmp;
        int find_bit = 0;

        // Loop to generate a unique determinant with k ones
        while(find_bit == 0) {
            det_tmp = generateDeterminantWithKOnes(numBits, k); // Generate a determinant
            find_bit = 1;  // Assume it's unique unless proven otherwise

            // Check for duplicates
            for (int ii = 0; ii < i; ii++) {
                if(det_tmp == psi[ii].det) {
                    find_bit = 0; // Reset find_bit to 0 to continue generating a new determinant
                    break; // Exit the for loop to try generating a new det_tmp
                }
            }
        }

        // Assign the unique determinant to the psi array
        psi[i].det = det_tmp;

        // Generate a random coefficient in the range [-1, 1]
        psi[i].coef = 2.0 * (double)rand() / RAND_MAX - 1.0;

        // Accumulate the square of the coefficient for normalization
        psi_norm += psi[i].coef * psi[i].coef;
    }

    // Calculate the normalization factor (1 divided by the square root of psi_norm)
    psi_norm = 1.0 / sqrt(psi_norm);

    // Normalize the coefficients
    for (int i = 0; i < n; i++) {
        psi[i].coef *= psi_norm;
    }
}

// Function to print the CI wavefunction
void printPsiTable(Psi* psi, int n) {
    // Print the header for the table
    printf("psi:\n");
    printf("det\tcoef\n");

    // Loop through each element in the psi array
    for (int i = 0; i < n; i++) {
        // Print the determinant and coefficient of the current element
        // %d formats the determinant as an integer
        // %.6f formats the coefficient as a floating-point number with 6 decimal places
        printf("%d\t%.6f\n", psi[i].det, psi[i].coef);
    }
}


