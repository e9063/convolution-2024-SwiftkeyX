#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int* copyArray(int* arr, int size) {
    int* newArr = malloc(size * sizeof(int));
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

void convole_parallel(int* A, int* F, int NA, int NF) {
    // First reverse array F
    int* F_copy = copyArray(F, NF);
    reverseArray(F_copy, NF);
    int* result = malloc(sizeof(int) * (NA - NF + 1));
    double start_time = omp_get_wtime(); // Start timing

    omp_set_num_threads(4);

    #pragma omp parallel for
    for (int j = 0; j < (NA - NF + 1); j++) {
        int sum = 0;  // Declare sum as private to each thread
        for (int i = 0; i < NF; i++) {
            int r = A[i + j] * F_copy[i];
            sum += r;
            // printf("%d*%d=%d threadNumber=%d, numberOfThread%d\n",A[i + j], F_copy[i], r, omp_get_thread_num(), omp_get_num_threads());
        }
        result[j] = sum;  // Each thread writes to its own result[j] safely
    }

    double end_time = omp_get_wtime(); // End timing
    // Print results
    printf("parallel: ");
    for (int i = 0; i < (NA - NF + 1); i++) {
        // printf("%d ", result[i]);
    }
    printf("\nTime taken (parallel): %f seconds\n", end_time - start_time);
    free(F_copy);  // Free allocated memory for F_copy
    free(result);  // Free allocated memory for result
}

int main() {
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int* A = malloc(sizeof(int) * NA);
    int* F = malloc(sizeof(int) * NF);

    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // Implement here
    convole_parallel(A, F, NA, NF);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}
