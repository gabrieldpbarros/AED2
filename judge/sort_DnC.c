#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *copyVector(int *mold, int size) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        copy[i] = mold[i];

    return copy;
}

void print(int *vt, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", vt[i]);
    printf("\n");
}   

int merge(int *v, int start, int middle, int end) {
    int i, j, k, comp = 0;
    int size1 = middle - start + 1;
    int size2 = end - middle;
    // Vetores auxiliares temporários
    int *left = (int*) malloc((size1 + 1) * sizeof(int));
    int *right = (int*) malloc((size2 + 1) * sizeof(int));

    for (i = 0; i < size1; i++)
        left[i] = v[start + i];
    for (j = 0; j < size2; j++)
        right[j] = v[middle + j + 1];
    left[i] = right[j] = INT_MAX;

    i = j = 0;

    for (k = start; k <= end; k++) {
        comp++;
        if (left[i] <= right[j])
            v[k] = left[i++];
        else
            v[k] = right[j++];
    }
    
    free(left);
    free(right);

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

int selectPivot(int *v, int start, int end, int *counter) {
    int middle = start + (end - start) / 2;

    (*counter)++;
    if (v[start] > v[middle])
        swap(&v[start], &v[middle]);
    
    (*counter)++;
    if (v[start] > v[end]) 
        swap(&v[start], &v[end]);

    (*counter)++;
    if (v[middle] > v[end])
        swap(&v[middle], &v[end]);

    swap(&v[middle], &v[end]); // Insere o pivo no final do vetor
    return v[end];
}

int partition(int *v, int start, int end, int *counter) {
    int pivot = selectPivot(v, start, end, counter);;

    int i, j = start - 1;
    for (i = start; i < end; i++) {
        (*counter)++;
        if (v[i] <= pivot)
            swap(&v[++j], &v[i]);  
    }

    swap(&v[++j], &v[end]);
    return j;
}

void quickSort(int *v, int start, int end, int *counter) {
    if (start < end) {
        int pivot = partition(v, start, end, counter);
        quickSort(v, start, pivot - 1, counter);
        quickSort(v, pivot + 1, end, counter);
    }
}

void insertionSort(int *v, int start, int end, int *counter) {
    int i, j;
    for (i = start + 1; i <= end; i++) {
        int key = v[i];
        j = i - 1;

        while (j >= start) {
            (*counter)++;
            if (v[j] > key)
                v[j + 1] = v[j--];
            else break;
        }

        v[j + 1] = key;
    }
}

void quickSortEF(int *v, int start, int end, int *counter) {
    if (end - start + 1 <= 5) 
        insertionSort(v, start, end, counter);
    else {
        int pivot = partition(v, start, end, counter);
        quickSortEF(v, start, pivot - 1, counter);
        quickSortEF(v, pivot + 1, end, counter);
    }
}

int main() {
    int size;
    scanf("%d", &size);

    int *vt = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        scanf("%d", &vt[i]);

    int *aux = copyVector(vt, size);
    int countMerge = mergeSort(aux, 0, size - 1);
    print(aux, size);
    printf("%d\n", countMerge);

    int countQuick;
    int *p = &countQuick;

    *p = 0;
    aux = copyVector(vt, size);
    quickSort(aux, 0, size - 1, p);
    print(aux, size);
    printf("%d\n", countQuick);
    
    *p = 0;
    quickSortEF(vt, 0, size - 1, p);
    print(vt, size);
    printf("%d\n", countQuick);

    free(vt);
    free(aux);

    return 0;
}