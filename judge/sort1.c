#include <stdio.h>
#include <stdlib.h>

void swap(long int *a, long int *b) {
    long int temp = *a;
    *a = *b;
    *b = temp;  
}

void copyVector(long int *model, long int *aux, int size) {
    for (int i = 0; i < size; i++)
        aux[i] = model[i];
}

void selectionSort(long int *v, int size) {
    int comp = 0, exc = 0;
    int i, j, min_index;
    for (i = 0; i < size - 1; i++) {
        min_index = i;
        for (j = i + 1; j < size; j++) {
            if (v[min_index] > v[j])
                min_index = j;
            comp++;
        }

        if (v[min_index] != v[i]) {
            swap(&v[min_index], &v[i]);
            exc++;
        }
    }

    printf("%d %d\n", comp, exc);
}

void bubbleSort(long int *v, int size) {
    int comp = 0, exc = 0;
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                swap(&v[j], &v[j + 1]);
                exc++;
            }
            comp++;
        }

        if (exc == 0)
            break;
    }

    printf("%d %d\n", comp, exc);
}

void insertionSort(long int *v, int size) {
    int comp = 0, exc = 0;
    int i, j;
    for (i = 1; i < size; i++) {
        long int key = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > key) {
            comp++;
            v[j + 1] = v[j--];
            exc++;
        }

        if (v[j] < key)
            comp++;

        if (v[j + 1] != key) {
            v[j + 1] = key;
            exc++;
        }
    }

    printf("%d %d\n", comp, exc);
}

int main() {
    int size;
    
    scanf("%d", &size);
    long int *v = malloc(size * sizeof(long int));
    long int *aux = malloc(size * sizeof(long int));

    for (int i = 0; i < size; i++)
        scanf("%ld", &v[i]);
        
    copyVector(v, aux, size);
    selectionSort(aux, size);

    copyVector(v, aux, size);
    bubbleSort(aux, size);
    // Como e o ultimo sort, posso usar o vetor diretamente
    insertionSort(v, size);
    
    free(v);
    free(aux);

    return 0;
}