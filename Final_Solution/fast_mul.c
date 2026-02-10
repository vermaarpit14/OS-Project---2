#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

double get_timestamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

void compute_sequential(int size, int *m1, int *m2, int *result) {
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            long sum = 0;
            for (int k = 0; k < size; k++) {
                sum += m1[r * size + k] * m2[k * size + c];
            }
            result[r * size + c] = sum;
        }
    }
}

int main(int argc, char *argv[]) {
    int matrix_size = 1000; 
    int num_workers = 4;

    if (argc >= 2) {
        matrix_size = atoi(argv[1]);
    }
    if (argc >= 3) {
        num_workers = atoi(argv[2]);
    }

    printf("Initializing Matrix: %dx%d | Workers: %d\n", matrix_size, matrix_size, num_workers);

    size_t bytes = matrix_size * matrix_size * sizeof(int);
    int *mat_A = (int *)malloc(bytes);
    int *mat_B = (int *)malloc(bytes);
    int *mat_C = (int *)malloc(bytes);

    if (!mat_A || !mat_B || !mat_C) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < matrix_size * matrix_size; i++) {
        mat_A[i] = rand() % 10;
        mat_B[i] = rand() % 10;
    }

    if (matrix_size <= 2000) {
        printf("Running Sequential Mode...\n");
        double t_start = get_timestamp();
        
        compute_sequential(matrix_size, mat_A, mat_B, mat_C);
        
        double t_end = get_timestamp();
        printf("Sequential Time: %.5f seconds\n", t_end - t_start);
    } else {
        printf("Sequential Time: Skipped (Size > 2000)\n");
    }

    fflush(stdout);

    printf("Running Parallel Mode...\n");
    double t_start_par = get_timestamp();

    int chunk_size = matrix_size / num_workers;

    for (int id = 0; id < num_workers; id++) {
        int start_row = id * chunk_size;
        int end_row = (id == num_workers - 1) ? matrix_size : (start_row + chunk_size);

        pid_t pid = fork();

        if (pid == 0) {
            for (int r = start_row; r < end_row; r++) {
                for (int c = 0; c < matrix_size; c++) {
                    long acc = 0;
                    for (int k = 0; k < matrix_size; k++) {
                        acc += mat_A[r * matrix_size + k] * mat_B[k * matrix_size + c];
                    }
                    mat_C[r * matrix_size + c] = acc;
                }
            }
            
            free(mat_A);
            free(mat_B);
            free(mat_C);
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
        }
    }

    for (int i = 0; i < num_workers; i++) {
        wait(NULL);
    }

    double t_end_par = get_timestamp();
    printf("Parallel Time:   %.5f seconds\n", t_end_par - t_start_par);

    free(mat_A);
    free(mat_B);
    free(mat_C);

    return 0;
}