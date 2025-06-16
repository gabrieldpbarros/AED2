#include <stdio.h>
#include <stdlib.h>

int h1(int key, int size) {
    return key % size;
}

int h2(int key, int size) {
    return 1 + key % (size - 1);
}

void insert(int *vt, int key, int vt_size) {
    int i = 0;
    while (i < vt_size) {
        int h = (h1(key, vt_size) + i * h2(key, vt_size)) % vt_size;
        if (vt[h] == -1) {
            vt[h] = key;
            return;
        }
        else i++;
    }
}

void searchRemove(int *vt, int key, int vt_size) {
    for (int i = 0; i < vt_size; i++) {
        int h = (h1(key, vt_size) + i * h2(key, vt_size)) % vt_size;
        if (vt[h] == -1)
            break;
        else {
            if (vt[h] == key) {
                int m = 0;
                while (m < vt_size) {
                    if (vt[m] == key) vt[m] = -2;
                    m++;
                }
                return;
            }    
        }
    }
    printf("Valor nao encontrado\n");
}

void print(int *vt, int vt_size) {
    for (int i = 0; i < vt_size; i++) {
        if (vt[i] == -1)
            printf("\\");
        else if (vt[i] == -2)
            printf("D");
        else
            printf("%d", vt[i]);
        
        if (i + 1 < vt_size)
            printf(" ");
    }
}

int main() {
    int m, num, key;
    scanf("%d", &m);

    int *vt = malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
        vt[i] = -1;
 
    while(1) {
        if(scanf("%d", &num) && num != -1)
            insert(vt, num, m);
        else break;
    }
    scanf("%d", &key);
    searchRemove(vt, key, m);
    
    print(vt, m);
    printf("\n");

    free(vt);  
    return 0;
}