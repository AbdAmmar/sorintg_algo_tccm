#ifndef UTILS

#define UTILS

#include "struct.h"

// Function to generate random integers between 0 and range - 1
void generateRandomArray(int arr[], int n, int range);

// Function to print the array
void printArray(int arr[], int n);

// Function to swap two elements in the array
void swap(int arr[], int i, int j);

// Function to get the maximum value in the array
int getMax(int arr[], int n);

// Function to get the maximum number of bits required to represent the largest number in the array
int getMaxBits(int arr[], int n);

// Function to generate a random integer with a fixed number of 1 bits
int generateDeterminantWithKOnes(int numBits, int k);

// initialize the wavefunction in a random way
void initializePsiTable(Psi* psi, int n, int k);

// Print CI wavefuntion
void printPsiTable(Psi* psi, int n);

#endif
