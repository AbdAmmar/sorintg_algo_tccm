#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "struct.h"

// Function to generate random integers between 0 and range - 1
void generateRandomArray(int arr[], int n, int range) {

    // Seed the random number generator with the current time
    srand(time(0));

    for (int i = 0; i < n; i++) {
        // Generate random integer between 0 and range - 1
        arr[i] = rand() % range;
    }
}

// Function to print the array
void printArray(int arr[], int n) {

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Function to swap two elements in the array
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Function to get the maximum value in the array
int getMax(int arr[], int n) {

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to get the maximum number of bits required to represent the largest number in the array
int getMaxBits(int arr[], int n) {

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int maxBits = 0;
    while (max > 0) {
        maxBits++;
        max >>= 1;
    }

    return maxBits;
}


// Function to generate a random integer with a fixed number of 1 bits
int generateDeterminantWithKOnes(int numBits, int k) {

    int det = 0;

    int positions[numBits];
    for (int i = 0; i < numBits; i++) {
        positions[i] = i;
    }

    // Seed the random number generator
    srand(time(NULL) + rand()); // Add random offset for uniqueness

    // Randomly select k positions for 1 bits
    for (int i = 0; i < k; i++) {
        int j = i + rand() % (numBits - i); // Select a random position
        // Swap to "remove" the chosen position
        int temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;
        // Set the bit at the chosen position
        det |= (1 << positions[i]);
    }

    // Ensure bit is positive by masking out the sign bit (MSB)
    if (det < 0) {
        det &= (1 << (numBits - 1)) - 1;  // Mask the sign bit if set
    }
    
    return det;
}

// initialize the wavefunction in a random way
void initializePsiTable(Psi* psi, int n, int k) {

    // number of bits in int
    int numBits = sizeof(int) * 8;

    // for normalization
    double psi_norm = 0.0;

    // Seed the random number generator
    srand(time(NULL));

    // Generate random positive integers for determinants and random doubles for coefficients
    for (int i = 0; i < n; i++) {

        // Determinants
        int find_bit = 0;
        int det_tmp;
        while(find_bit == 0) {
            det_tmp = generateDeterminantWithKOnes(numBits, k);
            find_bit = 1;  // Assume it's unique unless proven otherwise
            for (int ii = 0; ii < i; ii++) {
                // Duplicate found, set find_bit to 0 and break to retry
                if(det_tmp == psi[ii].det){
                    find_bit = 0; // Reset find_bit to 0 to continue generating a new determinant
                    break; // Exit the for loop to try generating a new det_tmp
                }
            }
        }
        psi[i].det = det_tmp;

        // Coefficients
        psi[i].coef = 2.0 * (double)rand() / RAND_MAX - 1.0;
        psi_norm += psi[i].coef * psi[i].coef;
    }

    // to avoid division and sqrt in the loop (multiplication is less expensive)
    psi_norm = 1.0 / sqrt(psi_norm);

    // Normalize the coefficients
    for (int i = 0; i < n; i++) {
        psi[i].coef *= psi_norm;
    }
}

// Print CI wavefunction
void printPsiTable(Psi* psi, int n) {
    printf("psi:\n");
    printf("det\tcoef\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.6f\n", psi[i].det, psi[i].coef);
    }
}

