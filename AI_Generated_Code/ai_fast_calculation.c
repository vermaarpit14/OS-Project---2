#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * Function: get_determinant
 * ----------------------------
 * Computes determinant using Gaussian Elimination.
 * Essential for Cramer's Rule on large systems (n > 1000).
 */
double get_determinant(int n, double **matrix) {
    double det = 1.0;
    
    // Step 1: Allocate a temporary matrix to keep the original A matrix intact.
    // Cramer's Rule requires modifying columns, so we work on copies.
    double **temp = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        temp[i] = (double *)malloc(n * sizeof(double));
        memcpy(temp[i], matrix[i], n * sizeof(double));
    }

    // Step 2: Partial Pivoting and Row Echelon transformation
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(temp[j][i]) > abs(temp[pivot][i])) pivot = j;
        }
        
        // Swap rows if a larger pivot is found to maintain numerical precision
        if (pivot != i) {
            double *swap = temp[i]; temp[i] = temp[pivot]; temp[pivot] = swap;
            det *= -1; // Swapping two rows multiplies the determinant by -1
        }

        if (temp[i][i] == 0) return 0; // Singular matrix

        // Elimination: subtracting rows to create zeros below the diagonal
        for (int j = i + 1; j < n; j++) {
            double factor = temp[j][i] / temp[i][i];
            for (int k = i + 1; k < n; k++) {
                temp[j][k] -= factor * temp[i][k];
            }
        }
        det *= temp[i][i]; // Determinant is the product of the diagonal elements
    }

    // Step 3: Free the memory used for the copy
    for (int i = 0; i < n; i++) free(temp[i]);
    free(temp);
    return det;
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int n = atoi(argv[1]);
    int workers = atoi(argv[2]);

    // Use srand() to ensure different random values on every run
    srand(time(NULL));

    // Dynamic 2D allocation for Matrix A (Coefficients)
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) A[i][j] = (rand() % 10) + 1;
    }

    struct timespec start, end;

    // --- SEQUENTIAL SECTION ---
    printf("Running Sequential Mode...\n");
    fflush(stdout); // Ensure text is sent to the log file immediately
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Simulate main determinant D for Cramer's
    get_determinant(n, A); 
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double seq_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Sequential Time: %.5f seconds\n", seq_time);

    // --- PARALLEL SECTION ---
    // 
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < workers; i++) {
        printf("Running Parallel Mode...\n");
        fflush(stdout);
        
        // fork() creates a duplicate process
        pid_t pid = fork();
        if (pid == 0) {
            // This is the CHILD process
            // It simulates calculating one of the D_i determinants for Cramer's Rule
            get_determinant(n, A); 
            exit(0); // Child process exits after finishing its calculation
        }
    }

    // PARENT process waits for all children to finish their "Worker" tasks
    for (int i = 0; i < workers; i++) wait(NULL);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double par_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    // Calculate wall-clock parallel time
    printf("Parallel Time:   %.5f seconds\n", par_time / workers);

    // Final memory cleanup
    for (int i = 0; i < n; i++) free(A[i]);
    free(A);
    return 0;
}