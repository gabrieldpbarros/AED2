#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483648

void merge(int *v, int start, int middle, int end) {
    int i, j, k;
    int size1 = middle - start + 1;
    int size2 = end - middle;
    // Vetores auxiliares temporários
    unsigned int *left = malloc((size1 + 1) * sizeof(unsigned int));
    unsigned int *right = malloc((size2 + 1) * sizeof(unsigned int));
    for (i = 0; i < size1; i++)
        left[i] = v[start + i];
    for (j = 0; j < size2; j++)
        right[j] = v[middle + j + 1];
    left[size1] = INFINITY;
    right[size2] = INFINITY;
    i = 0;
    j = 0;

    for (k = start; k < end + 1; k++) {
        if (left[i] <= right[j])
            v[k] = left[i++];
        else
            v[k] = right[j++];
    }
    
    free(left);
    free(right);
}

void mergeSort(int *v, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSort(v, start, middle);
        mergeSort(v, middle + 1, end);
        merge(v, start, middle, end);
    }
}

void swap(int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int selectPivot(int *v, int start, int end) { // ERRO AQUI
    int middle = start + (end - start) / 2;

    if (v[start] > v[middle])
        swap(&v[start], &v[middle]);
    if (v[start] > v[end - 1])
        swap(&v[start], &v[end]);
    if (v[middle] > v[end - 1])
        swap(&v[middle], &v[end]);

    return middle;
}

int partition(int *v, int start, int end) {
    int pivot_index = selectPivot(v, start, end);
    swap(&v[pivot_index], &v[end]); // Insere o pivo no final do vetor

    int i, j = 0;
    for (i = start; i < end - 1; i++)
        if (v[i] < v[end])
            swap(&v[++j], &v[i]);

    swap(&v[++j], &v[end]);
    return j;
}

void quickSort(int *v, int start, int end) {
    if (start < end) {
        int pivot = partition(v, start, end);
        quickSort(v, start, pivot - 1);
        quickSort(v, pivot + 1, end);
    }
}

void insertionSort() {

}

void quickSortEF(int *v, int start, int end) {
    if (end - start + 1 > 5) {
        int pivot = partition(v, start, end);
        quickSort(v, start, pivot - 1);
        quickSort(v, pivot + 1, end);
    } else
        insertionSort();
}

#define SIZE 6
int main() {
    int jorje[SIZE];
    int j = 0;
    for(int i = SIZE; i > 0; i--)
        jorje[j++] = i;
    for(int i = 0; i < SIZE; i++)
        printf("%d ", jorje[i]);
    printf("\n");

    quickSort(jorje, 0, 6);
    for(int i = 0; i < SIZE; i++)
        printf("%d ", jorje[i]);

    return 0;
}