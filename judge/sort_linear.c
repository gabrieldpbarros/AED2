#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int *keyMap(char *key) {
    int *map = calloc(128, sizeof(int));
    map[' '] = 0; // O espaco nao tem valor
    for (int i = 0; i < 26; i++)
        map[(int) key[i]] = i + 1; // Cada letra da chave possui um valor na ordenacao

    return map;
}

void low_case(char *str) {
    for (int i = 0; i < 20; i++)
        if ((int) str[i] > 64 && (int) str[i] < 91)
            str[i] = (int) str[i] + 32;
}

void formatSpaces(char *str, int word_size) {
    str[20] = '\0';
    for (int i = 19; i >= word_size; i--)
        str[i] = ' ';
}

void freeMatrix(int **mat, int size) {
    for (int i = 0; i < size; i++)
        free(mat[i]);
    free(mat);
}

void countingSort(char **words, int size, int pos, int *map, int **matCount, int radix_step) {
    int *count = calloc(27, sizeof(int));
    char **order = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++)
        order[i] = malloc(21 * sizeof(char));

    for (int i = 0; i < size; i++)
        count[map[(int)words[i][pos]]]++;

    for (int i = 1; i < 27; i++)
        count[i] += count[i - 1];

    for (int i = 0; i < 27; i++)
        matCount[radix_step][i] = count[i];

    for (int i = size - 1; i >= 0; i--) {
        int idx = map[(int)words[i][pos]];
        strcpy(order[--count[idx]], words[i]);
    }
    // Copia de volta
    for (int i = 0; i < size; i++)
        strcpy(words[i], order[i]);

    for (int i = 0; i < size; i++)
        free(order[i]);
    free(order);
    free(count);
}

void radixSort(char **words, int size, int max_len, int *map, int **matC) {
    for (int i = max_len - 1; i >= 0; i--)
        countingSort(words, size, i, map, matC, max_len - i - 1);
}

int main() {
    int size, i, j;
    scanf("%d", &size);
    // Recebe a chave de ordenacao
    char *key = (char*) malloc(26 * sizeof(char));
    scanf("%s", key);
    // Mapeia a chave com um vetor de 27 posicoes
    int *map = keyMap(key);
    // Aloca uma matriz para as stringst
    char **words = (char**) malloc(size * sizeof(char*));
    for (i = 0; i < size; i++)
        words[i] = (char*) malloc(21 * sizeof(char)); // o índice 20 será usado para armazenar '\0'

    i = 0;
    int highest  = 0;
    int aux = size;
    while (aux--) {
        scanf("%s", words[i]);
        low_case(words[i]);
        // Palavras em minusculo
        printf("%s.\n", words[i]);
        // Encontra a maior palavra e armazena o tamanho da palavra atual
        int temp = strlen(words[i]);
        if (temp > highest)
            highest = temp;
        // Posiciona os espacos
        formatSpaces(words[i++], temp);
    }
    // Tamanho da maior palavra
    printf("%d\n", highest);
    // Matriz para armazenar os vetores C
    int **matC = malloc(highest * sizeof(int*));
    for (int i = 0; i < highest; i++)
        matC[i] = calloc(27, sizeof(int));

    radixSort(words, size, highest, map, matC);
    // Indices counting sort
    for (i = 0; i < highest; i++) 
        for (j = 0; j < 27; j++)
            printf("%d%c", matC[i][j], j < 26 ? ' ' : '\n');
    // Palavras ordenadas
    for (int i = 0; i < size; i++)
        printf("%s\n", words[i]);

    free(key);
    free(map);
    freeMatrix(matC, highest);
    for (i = 0; i < size; i++)
        free(words[i]);
    free(words);

    return 0;
}