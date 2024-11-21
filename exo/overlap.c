#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Compares two Psi structures by their determinant values.
// a: Pointer to the first Psi structure.
// b: Pointer to the second Psi structure.
// Returns: Negative if the determinant of a is less than b, zero if equal, 
//          or positive if greater.
int compare_det(const void* a, const void* b) {
    Psi *psiA = (Psi*) a;
    Psi *psiB = (Psi*) b;
    return (psiA->det - psiB->det);
}


// Function to calculate the overlap between two sets of Psi structures in a naive way.
// N1: Number of elements in the first wavefunction.
// psi1: Pointer to the first set of Psi structures.
// N2: Number of elements in the second wavefunction.
// psi2: Pointer to the second set of Psi structures.
// Returns: The calculated overlap as a double value.
double naive_overlap(int N1, Psi* psi1, int N2, Psi* psi2) {

    double s = 0.0; // Initialize the overlap accumulator.

    // Iterate over all elements in the first wavefunction.
    for (int i = 0; i < N1; i++) {
        // For each element in the first wavefunction, iterate over all elements in the second wavefunctions.
        for (int j = 0; j < N2; j++) {
            // Check if the determinants of the current elements match.
            if (psi1[i].det == psi2[j].det) {
                // If they match, accumulate the product of their coefficients.
                s += psi1[i].coef * psi2[j].coef;
            }
        }
    }

    return s; // Return the calculated overlap.
}

// Function to calculate the overlap between two sets of Psi structures in an optimized way.
// N1: Number of elements in the first wavefunction.
// psi1: Pointer to the first set of Psi structures.
// N2: Number of elements in the second wavefunction.
// psi2: Pointer to the second set of Psi structures.
// Returns: The calculated overlap as a double value.
double smart_overlap(int N1, Psi* psi1, int N2, Psi* psi2) {

    // Sort both sets of Psi structures by their determinant values for efficient comparison.
    qsort(psi1, N1, sizeof(Psi), compare_det);
    qsort(psi2, N2, sizeof(Psi), compare_det);

    int i = 0; // Index for the first wavefunction.
    int j = 0; // Index for the second wavefunction.
    double s = 0.0; // Initialize the overlap accumulator.

    // Traverse both sorted sets using a two-pointer approach.
    while ((i < N1) && (j < N2)) {
        // If the determinants match, accumulate the product of their coefficients.
        if (psi1[i].det == psi2[j].det) {
            s += psi1[i].coef * psi2[j].coef;
            i++; // Move to the next element in both sets.
            j++;
        }
        // If the current determinant in the first set is smaller, move to the next element in the first set.
        else if (psi1[i].det < psi2[j].det) {
            i++;
        }
        // If the current determinant in the second set is smaller, move to the next element in the second set.
        else {
            j++;
        }
    }

    return s; // Return the calculated overlap.
}


/**
 * Main function to demonstrate the calculation of overlap between two CI wavefunctions 
 * (psi1 and psi2) using both naive and optimized methods. It also measures and compares
 * the execution times for these methods.
 */
int main() {

    // Number of electrons in the system.
    int Ne = 10;

    // Sizes of the CI wavefunctions.
    int N1 = 110000;  // Size of the first wavefunction (psi1).
    int N2 = 250000;  // Size of the second wavefunction (psi2).

    struct timespec start, end;  // Variables to measure elapsed time.
    double elapsed_time;         // Variable to store calculated time.

    // Allocate memory for the first wavefunction (psi1).
    Psi* psi1 = (Psi*) malloc(N1 * sizeof(Psi));
    if (psi1 == NULL) {  // Check if memory allocation was successful.
        printf("Memory allocation failed!\n");
        exit(1);  // Exit if memory allocation fails.
    }

    // Allocate memory for the second wavefunction (psi2).
    Psi* psi2 = (Psi*) malloc(N2 * sizeof(Psi));
    if (psi2 == NULL) {  // Check if memory allocation was successful.
        printf("Memory allocation failed!\n");
        exit(1);  // Exit if memory allocation fails.
    }

    // Initialize the first wavefunction with randomized or defined values.
    initializePsiTable(psi1, N1, Ne);
    printf("psi1 has been initialized.\n");

    // Initialize the second wavefunction with randomized or defined values.
    initializePsiTable(psi2, N2, Ne);
    printf("psi2 has been initialized.\n");

    // Measure and calculate overlap using the naive method.
    clock_gettime(CLOCK_REALTIME, &start);  // Record start time.
    double s_naive = naive_overlap(N1, psi1, N2, psi2);
    clock_gettime(CLOCK_REALTIME, &end);    // Record end time.
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("s_naive = %.6f, calculated in %.3f sec\n", s_naive, elapsed_time);

    // Measure and calculate overlap using the optimized (smart) method.
    clock_gettime(CLOCK_REALTIME, &start);  // Record start time.
    double s_smart = smart_overlap(N1, psi1, N2, psi2);
    clock_gettime(CLOCK_REALTIME, &end);    // Record end time.
    elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("s_smart = %.6f, calculated in %.3f sec\n", s_smart, elapsed_time);

    // Deallocate memory for the wavefunctions.
    free(psi1);
    free(psi2);

    // Set pointers to NULL to avoid dangling pointers.
    psi1 = NULL;
    psi2 = NULL;

    return 0;  // Return 0 to indicate successful execution.
}
