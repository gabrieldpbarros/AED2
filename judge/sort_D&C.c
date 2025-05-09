#include <stdio.h>
#include <stdlib.h>

int *copyVector(int *mold, int size) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        copy[i] = mold[i];

    return copy;
}

int merge(int *v, int start, int middle, int end) {
    int i, j, k, comp = 0;
    int size1 = middle - start + 1;
    int size2 = end - middle;
    // Vetores auxiliares temporários
    int *left = malloc(size1 * sizeof(int));
    int *right = malloc(size2 * sizeof(int));
    for (i = 0; i < size1; i++)
        left[i] = v[start + i];
    for (j = 0; j < size2; j++)
        right[j] = v[middle + j + 1];

    i = j = 0;
    k = start;

    while (i < size1 && j < size2) {
        comp++;
        if (left[i] <= right[j])
            v[k++] = left[i++];
        else
            v[k++] = right[j++];
    }

    while (i < size1)
        v[k++] = left[i++];
    while (j < size2)
        v[k++] = right[j++];
    
    free(left);
    free(right);
    printf("merge(%d, %d, %d): %d comp\n", start, middle, end, comp);

    return comp;
}

int mergeSort(int *v, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        return mergeSort(v, start, middle) + 
               mergeSort(v, middle + 1, end) + 
               merge(v, start, middle, end);
    }
    return 0;
}

void swap(int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int selectPivot(int *v, int start, int end) {
    int middle = start + (end - start) / 2;

    if (v[start] > v[middle])
        swap(&v[start], &v[middle]);
    if (v[start] > v[end - 1])
        swap(&v[start], &v[end - 1]);
    if (v[middle] > v[end - 1])
        swap(&v[middle], &v[end - 1]);

    return middle;
}

int partition(int *v, int start, int end) {
    int pivot_index = selectPivot(v, start, end);
    swap(&v[pivot_index], &v[end - 1]); // Insere o pivo no final do vetor
    int pivot = v[end - 1];

    int i, j = start;
    for (i = start; i < end - 1; i++)
        if (v[i] < pivot)
            swap(&v[j++], &v[i]);

    swap(&v[j], &v[end - 1]);
    return j;
}

int quickSort(int *v, int start, int end) {
    if (start < end) {
        int pivot = partition(v, start, end);
        quickSort(v, start, pivot);
        quickSort(v, pivot + 1, end);
    }
}

void insertionSort(int *v, int size) {
    int i, j;
    for (i = 1; i < size; i++) {
        int key = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > key)
            v[j + 1] = v[j--];

        v[j + 1] = key;
    }
}

int quickSortEF(int *v, int start, int end) {
    if (end - start > 5) {
        int pivot = partition(v, start, end);
        quickSortEF(v, start, pivot);
        quickSortEF(v, pivot + 1, end);
    } else {
        int size = end - start;
        insertionSort(&v[start], size);
    }
}

int main() {
    int size;
    scanf("%d", &size);

    int *vt = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        scanf("%d", &vt[i]);

    int *aux = copyVector(vt, size);
    int count = mergeSort(aux, 0, size - 1);
    printf("merge = %d\n", count);

    aux = copyVector(vt, size);
    count = quickSort(aux, 0, size);
    printf("quick = %d\n", count);

    count = quickSortEF(vt, 0, size);
    printf("quick eficiente = %d\n", count);

    return 0;
}