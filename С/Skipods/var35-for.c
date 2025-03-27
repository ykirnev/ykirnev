#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define Max(a,b) ((a)>(b)?(a):(b))

long long int N;
int THR = 0;
float maxeps = 0.1e-7;
int itmax = 100;
float eps;
float *A, *B;

void relax();
void resid();
void init();
void verify(FILE* f);

int main(int an, char **as) {
    double start_time, end_time;
    start_time = omp_get_wtime();
    if (an < 5) {
        fprintf(stderr, "Usage: %s <scale> <threads> <time_file> <output_file>\n", as[0]);
        return EXIT_FAILURE;
    }
    THR = strtoll(as[2], 0, 10);
    N = 2 * 2 * 2 * 2 * 2 * 2 * strtoll(as[1], 0, 10) + 2;
    omp_set_num_threads(THR);
    A = (float*)malloc(N * N * sizeof(float));
    B = (float*)malloc(N * N * sizeof(float));
    if (!A || !B) {
        fprintf(stderr, "Memory allocation failed!\n");
        return EXIT_FAILURE;
    }
    FILE *outf = fopen(as[4], "w");
    if (!outf) {
        fprintf(stderr, "Failed to open output file!\n");
        return EXIT_FAILURE;
    }
    init();
    for (int it = 1; it <= itmax; it++) {
        eps = 0.;
        relax();
        resid();
        fprintf(outf, "it=%4i   eps=%f\n", it, eps);
        if (eps < maxeps) break;
    }
    verify(outf);
    fclose(outf);
    end_time = omp_get_wtime();
    FILE *time_file = fopen(as[3], "w");
    if (time_file) {
        fprintf(time_file, "%f\n", end_time - start_time);
        fclose(time_file);
    }
    free(A);
    free(B);
    return 0;
}

void init() {
#pragma omp parallel for
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1) {
                A[j * N + i] = 0.0;
            } else {
                A[j * N + i] = (1.0 + i + j);
            }
        }
    }
}

void relax() {
#pragma omp parallel for
    for (int j = 2; j <= N - 3; j++) {
        for (int i = 2; i <= N - 3; i++) {
            B[j * N + i] = (A[(j - 2) * N + i] + A[(j - 1) * N + i] + A[(j + 2) * N + i] + A[(j + 1) * N + i] +
                            A[j * N + (i - 2)] + A[j * N + (i - 1)] + A[j * N + (i + 2)] + A[j * N + (i + 1)]) / 8.0;
        }
    }
}

void resid() {
#pragma omp parallel for reduction(max:eps)
    for (int j = 1; j <= N - 2; j++) {
        for (int i = 1; i <= N - 2; i++) {
            float e = fabs(A[j * N + i] - B[j * N + i]);
            A[j * N + i] = B[j * N + i];
            eps = Max(eps, e);
        }
    }
}

void verify(FILE* f) {
    float s = 0.0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            s += A[j * N + i] * (i + 1) * (j + 1) / (N * N);
        }
    }
    fprintf(f, "  S = %f\n", s);
}