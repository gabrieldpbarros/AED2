#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Funcoes auxiliares
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;  
}

int *copyVector(int *vt, int size) {
    int *new = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        new[i] = vt[i];

    return &new[0];
}

void print(int *vt, int size) {
    printf("\nVetor ordenado:\n");

    for (int i = 0; i < size; i++) {
        printf("%d", vt[i]);
        if (i + 1 < size) printf(" ");
    }
    
    free(vt);
    printf("\n");
}
// Algoritmos de ordenacao simples
void selectionSort(int *v, int size) {
    int i, j, min_index;
    for (i = 0; i < size - 1; i++) {
        min_index = i;
        for (j = i + 1; j < size; j++) 
            if (v[min_index] > v[j])
                min_index = j;

        if (v[min_index] != v[i])
            swap(&v[min_index], &v[i]);
    }

    // Adaptacao para este codigo
    print(v, size);
}

void bubbleSort(int *v, int size) {
    int exc = 0;
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) 
            if (v[j] > v[j + 1]) {
                swap(&v[j], &v[j + 1]);
                exc++;
            }

        if (exc == 0)
            break;
    }

    // Adaptacao para este codigo
    print(v, size);
}


void insertionSort(int *v, int size) {
    int i, j;
    for (i = 1; i < size; i++) {
        int key = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > key) 
            v[j + 1] = v[j--];

        if (v[j + 1] != key) 
            v[j + 1] = key;
    }

    // Adaptacao para este codigo
    print(v, size);
}

// Algoritmos de ordenacao com metodo Dividir e Conquistar
void merge(int *v, int start, int middle, int end) {
    int i, j, k;
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
}

void mergeSort(int *v, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSort(v, start, middle);
        mergeSort(v, middle + 1, end);
        merge(v, start, middle, end);
  }
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

void quickSort(int *v, int start, int end) {
    if (start < end) {
        int pivot = partition(v, start, end);
        quickSort(v, start, pivot);
        quickSort(v, pivot + 1, end);
    }
}

// Algoritmos de ordenacao com metodo Transformar e Conquistar
// Funcoes auxiliares
void maxHeapify(int *v, int index) {

}

void buildHeap(int *v, int length) {

}

int heapPop(int *v, int length) {

}

void heapSort(int *v, int length) {

}

// Algoritmos de ordenação sem comparação [O(n)]
int countingSort(int *v, int *ord, int sizeV, int max) { // Necessita que as chaves sejam INTEIROS
    int i;
    int *aux = calloc((max + 1), sizeof(int));
    for (i = 0; i < sizeV; i++)
        aux[v[i]]++;
    
    for (i = 1; i < max; i++)
        aux[i] += aux[i - 1];

    for (i = sizeV - 1; i > 0; i--) {
        ord[aux[v[i]]] = v[i];
        aux[v[i]]--;
    }

    free(aux);
}

void radixSort(int *v) {

}

void bucketSort() { // binSort

}

int main() {
    int size, i, k = 1;
    char st[15];
    
    printf("Insira o tamanho do vetor: ");
    scanf("%d", &size);
    
    srand(time(NULL));
    int *vt = malloc(size * sizeof(int));
    for(i = 0; i < size; i++)
        vt[i] = rand();

    printf("\nVetor inicial:\n");
    for(i = 0; i < size; i++)
        printf("%d ", vt[i]);
    printf("\n");

    while (k) {
        printf("\nDigite o algoritmo de ordenacao (selection, bubble, insertion, merge, quick), ou 0 para encerrar: ");
        scanf("%s", st);

        if (!strcmp(st, "selection"))
            selectionSort(copyVector(vt, size), size);

        else if (!strcmp(st, "bubble"))
            bubbleSort(copyVector(vt, size), size);

        else if (!strcmp(st, "insertion"))
            insertionSort(copyVector(vt, size), size);

        else if (!strcmp(st, "merge")) {
            int *aux = copyVector(vt, size);
            mergeSort(aux, 0, size);
            print(aux, size);
        }

        else if (!strcmp(st, "quick")) {
            int *aux = copyVector(vt, size);
            quickSort(aux, 0, size);
            print(aux, size);
        }

        else if(!strcmp(st, "0")) k = 0;

        else printf("\n[ERRO]\nDigite um argumento valido.\n");
    }

    return 0;
}