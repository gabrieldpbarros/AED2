// Gabriel Delgado Panovich de Barros - RA:176313
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // clock_gettime não funciona no windows

void linearSearch(long int *v, long int x) {
    for(long int i = 0; i < 100000000; i++)
        if(v[i] == x) return;

    return;
}

void binarySearch(long int *v, long int x, long int size) {
    long int start = 0;
    long int end = size - 1;

    while (start <= end) {
        long int middle = (start + end) / 2;

        if(v[middle] == x) return;
        else if(v[middle] > x) end = middle - 1;
        else start = middle + 1;
    }

    return;
}

void binaryRecursive(long int *v, long int x, long int start, long int end) {
    if (start > end) return; // Primeira condição de parada
    long int middle = (start + end) / 2;

    if (v[middle] == x) return; // Segunda condição de parada
    else if (v[middle] > x) binaryRecursive(v, x, start, middle - 1);
    else binaryRecursive(v, x, middle + 1, end);
}

double measureTime(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER freq) {
    return (double) (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
}

int main() {
    long int size = 100000000, i;
    long int *v = malloc(size * sizeof(long int));
    LARGE_INTEGER start, end, freq;
    double lin_best, lin_worst, lin_average,
           bin_best, bin_worst, bin_average,
           bin_rec_best, bin_rec_worst, bin_rec_average;

    QueryPerformanceFrequency(&freq);
    // Preenche o vetor ordenadamente
    for(i = 0; i < size; i++)
        v[i] = i + 1;

    // Linear melhor caso
    QueryPerformanceCounter(&start);
    linearSearch(v, 1);
    QueryPerformanceCounter(&end);
    lin_best = measureTime(start, end, freq);

    // Linear pior caso
    QueryPerformanceCounter(&start);
    linearSearch(v, -1);
    QueryPerformanceCounter(&end);
    lin_worst = measureTime(start, end, freq);

    // Linear caso médio
    double somatorio = 0;
    for(i = 0; i < 20; i++){
        int random = rand() % size;

        QueryPerformanceCounter(&start);
        linearSearch(v, random);
        QueryPerformanceCounter(&end);
        somatorio += measureTime(start, end, freq);
    }
    lin_average = somatorio / 20;

    // Binária melhor caso
    QueryPerformanceCounter(&start);
    binarySearch(v, size / 2, size);
    QueryPerformanceCounter(&end);
    bin_best = measureTime(start, end, freq);

    // Binária pior caso
    QueryPerformanceCounter(&start);
    binarySearch(v, -1, size);
    QueryPerformanceCounter(&end);
    bin_worst = measureTime(start, end, freq);

    // Binária caso médio
    somatorio = 0;
    for(i = 0; i < 20; i++){
        int random = rand() % size;

        QueryPerformanceCounter(&start);
        binarySearch(v, random, size);
        QueryPerformanceCounter(&end);
        somatorio += measureTime(start, end, freq);
    }
    bin_average = somatorio / 20;

    // Binária recursiva melhor caso
    QueryPerformanceCounter(&start);
    binaryRecursive(v, size / 2, 0, size - 1);
    QueryPerformanceCounter(&end);
    bin_rec_best = measureTime(start, end, freq);

    // Binária recursiva pior caso
    QueryPerformanceCounter(&start);
    binaryRecursive(v, -1, 0, size - 1);
    QueryPerformanceCounter(&end);
    bin_rec_worst = measureTime(start, end, freq);

    // Binária recursiva caso médio
    somatorio = 0;
    for(i = 0; i < 20; i++){
        int random = rand() % size;

        QueryPerformanceCounter(&start);
        binaryRecursive(v, random, 0, size - 1);
        QueryPerformanceCounter(&end);
        somatorio += measureTime(start, end, freq);
    }
    bin_rec_average = somatorio / 20;

    printf("\n");
    // Resultados
    printf("[BUSCA LINEAR]:\n");
    printf("Melhor caso: %.4f ms\n", lin_best);
    printf("Pior caso: %.4f ms\n", lin_worst);
    printf("Caso medio: %.4f ms\n\n", lin_average);

    printf("[BUSCA BINARIA]:\n");
    printf("Melhor caso: %.4f ms\n", bin_best);
    printf("Pior caso: %.4f ms\n", bin_worst);
    printf("Caso medio: %.4f ms\n\n", bin_average);

    printf("[BUSCA BINARIA RECURSIVA]:\n");
    printf("Melhor caso: %.4f ms\n", bin_rec_best);
    printf("Pior caso: %.4f ms\n", bin_rec_worst);
    printf("Caso medio: %.4f ms\n\n", bin_rec_average);

    free(v);
    return 0;
}