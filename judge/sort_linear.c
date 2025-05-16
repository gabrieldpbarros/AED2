#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *newVt(int size) {
    int *new = calloc(size, sizeof(int));
    return new;
}

void countingSort(int *vt, int *ord, int ceil, int size) {
    int i;
    int *aux = newVt(ceil + 1);
    for (int i = 0; i < size; i++)
        aux[vt[i]]++;
}

int main() {

    return 0;
}