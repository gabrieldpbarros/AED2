#include <stdio.h>
#include <stdlib.h>

// ARN
int Max(int a, int b) {
    return (a > b) ? a : b;
}

typedef enum { RED, BLACK } Color;

typedef struct node {
    int key;
    Color cor;
    struct node *left, *right, *father;
} ARN;

int mudancas_cor_avp = 0;
int rotacoes_avp = 0;
// Auxiliares
void chageColor(Color *cor, Color new) {
    if (*cor != new) {
        *cor = new;
        mudancas_cor_avp++;
    }
}

ARN *newNodeARN(int key) {
    ARN *new = malloc(sizeof(ARN));
    new->key = key;
    new->cor = RED;
    new->left = new->right = new->father = NULL;
    return new;
}

void transplant(ARN **raiz, ARN *u, ARN *v) {
    if (!u->father)
        *raiz = v;
    else if (u == u->father->left)
        u->father->left = v;
    else
        u->father->right = v;
    if (v)
        v->father = u->father;
}

ARN *minARN(ARN *node) {
    while (node->left)
        node = node->left;
    return node;
}

int nodeHeight(ARN *node) {
    if (!node)
        return -1;
    int he = nodeHeight(node->left);
    int hd = nodeHeight(node->right);
    return 1 + Max(he, hd);
}

int redHeight(ARN *node) {
    if (!node)
        return 0;
    int he = redHeight(node->left);
    int hd = redHeight(node->right);
    int verm = (node->cor == RED) ? 1 : 0;
    int maior = Max(he, hd);
    if ((he >= hd && node->left && node->left->cor == RED) || 
        (hd > he && node->right && node->right->cor == RED))
        return maior;
    return maior + verm;
}

ARN *rotateLeftARN(ARN *raiz, ARN *x) {
    ARN *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->father = x;
    y->father = x->father;
    if (!x->father)
        raiz = y;
    else if (x == x->father->left)
        x->father->left = y;
    else
        x->father->right = y;
    y->left = x;
    x->father = y;
    rotacoes_avp++;
    return raiz;
}

ARN *rotateRightARN(ARN *raiz, ARN *y) {
    ARN *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->father = y;
    x->father = y->father;
    if (!y->father)
        raiz = x;
    else if (y == y->father->left)
        y->father->left = x;
    else
        y->father->right = x;
    x->right = y;
    y->father = x;
    rotacoes_avp++;
    return raiz;
}

ARN *ajustarInsercaoARN(ARN *raiz, ARN *z) {
    while (z->father && z->father->cor == RED) {
        ARN *avo = z->father->father;
        if (z->father == avo->left) {
            ARN *tio = avo->right;
            if (tio && tio->cor == RED) {
                chageColor(&z->father->cor, BLACK);
                chageColor(&tio->cor, BLACK);
                chageColor(&avo->cor, RED);
                z = avo;
            } else {
                if (z == z->father->right) {
                    z = z->father;
                    raiz = rotateLeftARN(raiz, z);
                }
                chageColor(&z->father->cor, BLACK);
                chageColor(&avo->cor, RED);
                raiz = rotateRightARN(raiz, avo);
            }
        } else {
            ARN *tio = avo->left;
            if (tio && tio->cor == RED) {
                chageColor(&z->father->cor, BLACK);
                chageColor(&tio->cor, BLACK);
                chageColor(&avo->cor, RED);
                z = avo;
            } else {
                if (z == z->father->left) {
                    z = z->father;
                    raiz = rotateRightARN(raiz, z);
                }
                chageColor(&z->father->cor, BLACK);
                chageColor(&avo->cor, RED);
                raiz = rotateLeftARN(raiz, avo);
            }
        }
    }
    if (raiz->cor != BLACK)
        raiz->cor = BLACK;
    return raiz;
}
// Metodos
ARN *insertARN(ARN *raiz, int key) {
    ARN *z = newNodeARN(key);
    ARN *y = NULL;
    ARN *x = raiz;
    while (x) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->father = y;
    if (!y)
        raiz = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    return ajustarInsercaoARN(raiz, z);
}

ARN *searchARN(ARN *raiz, int chave) {
    if (raiz == NULL || raiz->key == chave)
    return raiz;
    if (chave < raiz->key) 
    return searchARN(raiz->left, chave);
    else 
    return searchARN(raiz->right, chave);
}

ARN* removeARN(ARN* raiz, int chave) {
    ARN* z = searchARN(raiz, chave);
    if (!z)
        return raiz;
    if (!z->left) 
        transplant(&raiz, z, z->right);
    else if (!z->right) 
        transplant(&raiz, z, z->left);
    else {
        ARN *y = minARN(z->right);
        if (y->father != z) {
            transplant(&raiz, y, y->right);
            y->right = z->right;
            if (y->right) y->right->father = y;
        }
        transplant(&raiz, z, y);
        y->left = z->left;
        if (y->left) y->left->father = y;
    }
    free(z);
    return raiz;
}
// Impressao
void printNodeHeight(ARN* node) {
    if (!node)
        return;
    int h = nodeHeight(node);
    int he = node->left ? nodeHeight(node->left) + 1 : 0;
    int hd = node->right ? nodeHeight(node->right) + 1 : 0;
    printf("%d,%d,%d\n", h, he, hd);
}
// Free
void freeARN(ARN *root) {
    if (root != NULL) {
        freeARN(root->left);
        freeARN(root->right);
        free(root);
    }
}

int main() {
    int num;
    ARN *arn = NULL;

    while (scanf("%d", &num) == 1 && num >= 0)
        arn = insertARN(arn, num);
    printNodeHeight(arn); // Altura da arvore

    int busca[100], tam = 0;
    while (scanf("%d", &num) == 1 && num >= 0)
        busca[tam++] = num;
    for (int i = 0; i < tam; i++) {
        ARN *node = searchARN(arn, busca[i]);
        if (node) {
            printNodeHeight(node);
            arn = removeARN(arn, busca[i]);
        } else
            arn = insertARN(arn, busca[i]);

    }

    if (scanf("%d", &num) == 1) {
        ARN *no = searchARN(arn, num);
        if (!no)
            printf("Valor nao encontrado\n");
        else
            printf("%d\n", redHeight(no));
    }

    freeARN(arn);

    return 0;
}