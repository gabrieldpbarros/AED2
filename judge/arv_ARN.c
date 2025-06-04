#include <stdio.h>
#include <stdlib.h>

// AVL
typedef struct AB {
    int value;
    int height;
    int bal_fact;
    struct AB *left, *right;
} tree;

int rotacoes_avl = 0;

int Max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(tree *node) {
    return node ? node->height : -1;
}

tree* createNodeAVL(int n) {
    tree *new_node = (tree*)malloc(sizeof(tree));
    new_node->value = n;
    new_node->height = 0;
    new_node->bal_fact = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

tree *LL(tree *subtree) {
    tree *pA = subtree;
    tree *pB = subtree->left;
    pA->left = pB->right;
    pB->right = pA;
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), pA->height) + 1;
    return pB;
}

tree *RR(tree *subtree) {
    tree *pA = subtree;
    tree *pB = subtree->right;
    pA->right = pB->left;
    pB->left = pA;
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->right), pA->height) + 1;
    return pB;
}

tree *LR(tree *subtree) {
    tree *pA = subtree;
    tree *pB = pA->left;
    tree *pC = pB->right;
    pB->right = pC->left;
    pC->left = pB;
    pA->left = pC->right;
    pC->right = pA;
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), getHeight(pB->right)) + 1;
    pC->height = Max(pA->height, pB->height) + 1;
    return pC;
}

tree *RL(tree *subtree) {
    tree *pA = subtree;
    tree *pB = pA->right;
    tree *pC = pB->left;
    pB->left = pC->right;
    pC->right = pB;
    pA->right = pC->left;
    pC->left = pA;
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), getHeight(pB->right)) + 1;
    pC->height = Max(pA->height, pB->height) + 1;
    return pC;
}

tree *rotateAB(tree *subtree) {
    if (subtree->bal_fact > 1) {
        if (subtree->left->bal_fact > 0) {
            rotacoes_avl++;
            return LL(subtree);
        } else {
            rotacoes_avl++;
            return LR(subtree);
        }
    } else if (subtree->bal_fact < -1) {
        if (subtree->right->bal_fact < 0) {
            rotacoes_avl++;
            return RR(subtree);
        } else {
            rotacoes_avl++;
            return RL(subtree);
        }
    }
    return subtree;
}

tree* insertAVL(tree *root, int value) {
    if (root == NULL) return createNodeAVL(value);
    if (value < root->value)
        root->left = insertAVL(root->left, value);
    else if (value > root->value)
        root->right = insertAVL(root->right, value);

    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    root->height = Max(lh, rh) + 1;
    root->bal_fact = lh - rh;
    return rotateAB(root);
}

void maxHeight(tree *root) {
    int he = getHeight(root->left) + 1;
    int hd = getHeight(root->right) + 1;
    printf("%d,%d,%d\n", root->height, he, hd);
}

void freeAVL(tree *root) {
    if (root != NULL) {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}

// ARN
typedef enum { RED, BLACK } Color;

typedef struct ARN {
    int key;
    Color cor;
    struct ARN *left, *right, *father;
} ARN;

int mudancas_cor_avp = 0;
int rotacoes_avp = 0;

void chageColor(Color *cor, Color new) {
    if (*cor != new) {
        *cor = new;
        mudancas_cor_avp++;
    }
}

ARN* newNodeARN(int key) {
    ARN* new = malloc(sizeof(ARN));
    new->key = key;
    new->cor = RED;
    new->left = new->right = new->father = NULL;
    return new;
}

ARN* rotateLeftARN(ARN* raiz, ARN* x) {
    ARN* y = x->right;
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

ARN* rotateRightARN(ARN* raiz, ARN* y) {
    ARN* x = y->left;
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

ARN* ajustarInsercaoAVP(ARN* raiz, ARN* z) {
    while (z->father && z->father->cor == RED) {
        ARN* avo = z->father->father;
        if (z->father == avo->left) {
            ARN* tio = avo->right;
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
            ARN* tio = avo->left;
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

ARN* insertARN(ARN* raiz, int key) {
    ARN* z = newNodeARN(key);
    ARN* y = NULL;
    ARN* x = raiz;
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
    return ajustarInsercaoAVP(raiz, z);
}

int heightARN(ARN* no) {
    if (!no) return -1;
    int he = heightARN(no->left);
    int hd = heightARN(no->right);
    return 1 + Max(he, hd);
}

int blackHeightARN(ARN* no) {
    if (!no) return 0;
    int he = blackHeightARN(no->left);
    int hd = blackHeightARN(no->right);
    int cor = (no->cor == BLACK) ? 1 : 0;
    return cor + Max(he, hd);
}

void blackHeight(ARN* root) {
    int h = heightARN(root);
    int he = root->left ? heightARN(root->left) + 1 : 0;
    int hd = root->right ? heightARN(root->right) + 1 : 0;
    printf("%d,%d,%d\n", h, he, hd);
}

void printChanges(tree* root_avl, ARN* root_avp) {
    printf("%d\n", blackHeightARN(root_avp));
    printf("%d,%d,%d\n", mudancas_cor_avp, rotacoes_avp, rotacoes_avl);
}

void freeARN(ARN *root) {
    if (root != NULL) {
        freeARN(root->left);
        freeARN(root->right);
        free(root);
    }
}

int main() {
    int num;
    tree *AVL = NULL;
    ARN *ARN = NULL;

    while (scanf("%d", &num) == 1 && num >= 0) {
        AVL = insertAVL(AVL, num);
        ARN = insertARN(ARN, num);
    }

    maxHeight(AVL);
    blackHeight(ARN);
    printChanges(AVL, ARN);

    freeAVL(AVL);
    freeARN(ARN);

    return 0;
}