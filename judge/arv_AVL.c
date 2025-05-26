#include <stdio.h>
#include <stdlib.h>

typedef struct AB {
    int value;
    int height;
    int bal_fact;
    struct AB *left;
    struct AB *right;
} tree;

// Funcoes auxiliares
int Max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(tree *node) {
    return node ? node->height : -1;
}

tree* createNode(int n) {
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
    // Atualiza a altura
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), pA->height) + 1;
    return pB;
}

tree *RR(tree *subtree) {
    tree *pA = subtree;
    tree *pB = subtree->right;
    pA->right = pB->left;
    pB->left = pA;
    // Atualiza a altura
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->right), pA->height) + 1;
    return pB;
}

tree *LR(tree *subtree) {
    tree *pA = subtree;
    tree *pB = pA->left;
    if (!pB || !pB->right) // proteção contra ponteiros nulos
        return pA; 

    tree *pC = pB->right;
    pB->right = pC->left;
    pC->left = pB;
    pA->left = pC->right;
    pC->right = pA;

    // Atualiza alturas
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), getHeight(pB->right)) + 1;
    pC->height = Max(pA->height, pB->height) + 1;

    return pC;
}

tree *RL(tree *subtree) {
    tree *pA = subtree;
    tree *pB = pA->right;
    if (!pB || !pB->left) // proteção contra ponteiros nulos
        return pA;

    tree *pC = pB->left;
    pB->left = pC->right;
    pC->right = pB;
    pA->right = pC->left;
    pC->left = pA;

    // Atualiza alturas
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), getHeight(pB->right)) + 1;
    pC->height = Max(pA->height, pB->height) + 1;

    return pC;
}

tree* rotateAB(tree *node) {
    if (node->bal_fact > 1) {
        if (node->left->bal_fact >= 0)
            return LL(node);
        else
            return LR(node);
    } else if (node->bal_fact < -1) {
        if (node->right->bal_fact <= 0)
            return RR(node);
        else
            return RL(node);
    }
    return node;
}

tree* insertAVL(tree *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insertAVL(root->left, value);
    else if (value > root->value)
        root->right = insertAVL(root->right, value);
    else
        return root;
    // Corrige as alturas e fatores de balanceamento
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    root->height = Max(leftHeight, rightHeight) + 1;
    root->bal_fact = leftHeight - rightHeight;
    return rotateAB(root);
}

tree* findMin(tree* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

tree* removeAVL(tree* root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->value) {
        root->left = removeAVL(root->left, value);
    } else if (value > root->value) {
        root->right = removeAVL(root->right, value);
    } else {
        if (root->left == NULL || root->right == NULL) {
            tree* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            tree* temp = findMin(root->right);
            root->value = temp->value;
            root->right = removeAVL(root->right, temp->value);
        }
    }
    // Atualiza a altura e fator de balanceamento
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    root->height = Max(leftHeight, rightHeight) + 1;
    root->bal_fact = leftHeight - rightHeight;
    return rotateAB(root);
}

int binSearch(tree *root, int value) {
    if (root == NULL) return 0;
    if (root->value == value) return 1;
    return (value < root->value) ? binSearch(root->left, value) : binSearch(root->right, value);
}

tree* findNode(tree* root, int value) {
    if (root == NULL || root->value == value) return root;
    return (value < root->value) ? findNode(root->left, value) : findNode(root->right, value);
}

void printHeights(tree *root) {
    if (!root) {
        printf("ARVORE VAZIA\n");
        return;
    }
    int he = getHeight(root->left) + 1;
    int hd = getHeight(root->right) + 1;
    printf("%d, %d, %d\n", root->height, he, hd);
}

void checkAndPrint(tree* root, int a, int b, int *printed, int *firstPrinted) {
    if (!root) return;
    if (root->value > a) checkAndPrint(root->left, a, b, printed, firstPrinted);
    if (root->value >= a && root->value <= b) {
        if (*firstPrinted) printf(", ");
        printf("%d", root->value);
        *firstPrinted = 1;
        *printed = 1;
    }
    if (root->value < b) checkAndPrint(root->right, a, b, printed, firstPrinted);
}

void printInRangeWithHeights(tree* root, int a, int b) {
    if (!root) return;
    if (root->value > a) printInRangeWithHeights(root->left, a, b);
    if (root->value >= a && root->value <= b) {
        tree* node = findNode(root, root->value);
        int hl = getHeight(node->left) + 1;
        int hr = getHeight(node->right) + 1;
        printf("%d, %d, %d\n", node->height, hl, hr);
    }
    if (root->value < b) printInRangeWithHeights(root->right, a, b);
}

void freeTree(tree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int num;
    tree *AVL = NULL;

    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        AVL = insertAVL(AVL, num);
    }

    printHeights(AVL);

    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        if (binSearch(AVL, num)) 
            AVL = removeAVL(AVL, num);
        else
            AVL = insertAVL(AVL, num);
    }

    printHeights(AVL);

    int printed = 0, firstPrinted = 0;
    int a, b;
    scanf("%d %d", &a, &b);

    checkAndPrint(AVL, a, b, &printed, &firstPrinted);
    if (!printed) printf("NADA A EXIBIR\n");
    else {
        printf("\n");
        printInRangeWithHeights(AVL, a, b);
    }

    freeTree(AVL);
    return 0;
}