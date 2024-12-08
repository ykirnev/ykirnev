#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define MAX_VAL(a, b) ((a) > (b) ? (a) : (b))
#define BORDER_VALUE 0.0f

long long N;
long long THREAD_COUNT = 1;
float MAX_ERROR = 0.1e-7f;
int MAX_ITER = 100;

float **currentGrid, **nextGrid;
float epsilon;

void initializeGrids();
void performRelaxation();
void calculateResiduals();
void calculateFinalResult(FILE *output);
void freeMemory();

// Основная функция
int main(int argc, char **argv) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <size> <threads> <time_file> <log_file>\n", argv[0]);
        return 1;
    }

    double start_time, end_time;
    start_time = omp_get_wtime();
    THREAD_COUNT = strtoll(argv[2], NULL, 10);
    N = (1 << 6) * strtoll(argv[1], NULL, 10) + 2;
    currentGrid = malloc(N * sizeof(float *));
    nextGrid = malloc(N * sizeof(float *));
    for (int i = 0; i < N; ++i) {
        currentGrid[i] = malloc(N * sizeof(float));
        nextGrid[i] = malloc(N * sizeof(float));
    }

    FILE *logFile = fopen(argv[4], "w");
    if (!logFile) {
        perror("Unable to open log file");
        return 1;
    }

    initializeGrids();
    for (int iteration = 1; iteration <= MAX_ITER; ++iteration) {
        epsilon = 0.0f;

#pragma omp parallel num_threads(THREAD_COUNT)
        {
            performRelaxation();
#pragma omp barrier

#pragma omp single
            calculateResiduals();
        }

        fprintf(logFile, "Iteration %4d: Epsilon = %.8f\n", iteration, epsilon);
        if (epsilon < MAX_ERROR) {
            break;
        }
    }

    calculateFinalResult(logFile);
    fclose(logFile);

    // Запись времени выполнения
    end_time = omp_get_wtime();
    FILE *timeFile = fopen(argv[3], "w");
    if (timeFile) {
        fprintf(timeFile, "%.6f\n", end_time - start_time);
        fclose(timeFile);
    }

    // Очистка памяти
    freeMemory();
    return 0;
}

// Инициализация сетки
void initializeGrids() {
#pragma omp parallel for num_threads(THREAD_COUNT)
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (x == 0 || x == N - 1 || y == 0 || y == N - 1) {
                currentGrid[x][y] = BORDER_VALUE;
            } else {
                currentGrid[x][y] = 1.0f + x + y;
            }
        }
    }
}

// Релаксация
void performRelaxation() {
#pragma omp for schedule(static)
    for (int y = 2; y < N - 2; ++y) {
        for (int x = 2; x < N - 2; ++x) {
            nextGrid[x][y] = (currentGrid[x - 2][y] + currentGrid[x - 1][y] +
                              currentGrid[x + 2][y] + currentGrid[x + 1][y] +
                              currentGrid[x][y - 2] + currentGrid[x][y - 1] +
                              currentGrid[x][y + 2] + currentGrid[x][y + 1]) / 8.0f;
        }
    }
}

// Расчет невязки
void calculateResiduals() {
#pragma omp for schedule(static) reduction(max:epsilon)
    for (int y = 1; y < N - 1; ++y) {
        for (int x = 1; x < N - 1; ++x) {
            float diff = fabsf(currentGrid[x][y] - nextGrid[x][y]);
            currentGrid[x][y] = nextGrid[x][y];
            epsilon = MAX_VAL(epsilon, diff);
        }
    }
}

// Подсчет результата
void calculateFinalResult(FILE *output) {
    float sum = 0.0f;

#pragma omp parallel for reduction(+:sum) num_threads(THREAD_COUNT)
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            sum += currentGrid[x][y] * (x + 1) * (y + 1) / (N * N);
        }
    }

    fprintf(output, "Final Sum: %.8f\n", sum);
}

// Очистка памяти
void freeMemory() {
    for (int i = 0; i < N; ++i) {
        free(currentGrid[i]);
        free(nextGrid[i]);
    }
    free(currentGrid);
    free(nextGrid);
}
