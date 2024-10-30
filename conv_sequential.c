#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to create a copy of the array
int* copyArray(int* arr, int size) {
    int* newArr = malloc(size * sizeof(int));
    if (newArr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    int temp;

    while (start < end) {
        // Swap the elements
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move to the next pair of elements
        start++;
        end--;
    }
}

void convole_sequential(int* A, int* F, int NA, int NF) {
    // First reverse array F
    int* F_copy = copyArray(F, NF);
    reverseArray(F_copy, NF);
    int* result = malloc(sizeof(int) * (NA - NF + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(F_copy);
        exit(EXIT_FAILURE);
    }

    clock_t start_time = clock(); // Start timing

    for (int j = 0; j < (NA - NF + 1); j++) {
        int sum = 0;
        for (int i = 0; i < NF; i++) {
            int r = A[i + j] * F_copy[i];
            sum += r;
        }
        result[j] = sum;
    }

    clock_t end_time = clock(); // End timing

    // Output results
    for (int i = 0; i < (NA - NF + 1); i++) {
        printf("%d\n", result[i]);
    }
    
    // Calculate time taken
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    // printf("\nTime taken (sequential): %f seconds\n", time_taken);

    free(F_copy);  // Free allocated memory for F_copy
    free(result);  // Free allocated memory for result
}

int main() {
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int* A = malloc(sizeof(int) * NA);
    int* F = malloc(sizeof(int) * NF);
    if (A == NULL || F == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc ----

    // Implement convolution
    convole_sequential(A, F, NA, NF);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}
