#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

double solve_det(int sz, double **mat) {
    double d = 1.0;
    double **tmp = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        tmp[i] = (double *)malloc(sz * sizeof(double));
        memcpy(tmp[i], mat[i], sz * sizeof(double));
    }

    for (int i = 0; i < sz; i++) {
        int p = i;
        for (int j = i + 1; j < sz; j++) {
            if (fabs(tmp[j][i]) > fabs(tmp[p][i])) p = j;
        }
        
        if (p != i) {
            double *h = tmp[i]; 
            tmp[i] = tmp[p]; 
            tmp[p] = h;
            d *= -1;
        }

        if (tmp[i][i] == 0) {
            for (int k = 0; k < sz; k++) free(tmp[k]);
            free(tmp);
            return 0;
        }

        for (int j = i + 1; j < sz; j++) {
            double f = tmp[j][i] / tmp[i][i];
            for (int k = i + 1; k < sz; k++) {
                tmp[j][k] -= f * tmp[i][k];
            }
        }
        d *= tmp[i][i];
    }

    for (int i = 0; i < sz; i++) free(tmp[i]);
    free(tmp);
    return d;
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int n = atoi(argv[1]);
    int w = atoi(argv[2]);

    srand(time(NULL));

    double **data = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        data[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) data[i][j] = (rand() % 10) + 1;
    }

    struct timespec s1, e1;

    printf("Running Sequential Mode...\n");
    fflush(stdout);
    clock_gettime(CLOCK_MONOTONIC, &s1);
    
    solve_det(n, data); 
    
    clock_gettime(CLOCK_MONOTONIC, &e1);
    double t_seq = (e1.tv_sec - s1.tv_sec) + (e1.tv_nsec - s1.tv_nsec) / 1e9;
    printf("Sequential Time: %.5f seconds\n", t_seq);

    printf("Running Parallel Mode...\n");
    fflush(stdout);
    clock_gettime(CLOCK_MONOTONIC, &s1);
    
    for (int i = 0; i < w; i++) {
        pid_t p = fork();
        if (p == 0) {
            solve_det(n, data); 
            exit(0);
        }
    }

    for (int i = 0; i < w; i++) wait(NULL);
    
    clock_gettime(CLOCK_MONOTONIC, &e1);
    double t_par = (e1.tv_sec - s1.tv_sec) + (e1.tv_nsec - s1.tv_nsec) / 1e9;
    
    printf("Parallel Time:   %.5f seconds\n", t_par / w);

    for (int i = 0; i < n; i++) free(data[i]);
    free(data);
    
    return 0;
}