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
tree* createNode(int n) {
    tree *new_node = (tree*)malloc(sizeof(tree));
    new_node->value = n;
    new_node->height = 0;
    new_node->bal_fact = 0;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int getHeight(tree *node) {
    return node ? node->height : -1;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

tree *findMin(tree* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}
// Rotacoes
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
    tree *pC = pB->right;
    pB->right = pC->left;
    pC->left = pB;
    pA->left = pC->right;
    pC->right = pA;
    // Atualiza a altura
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
    // Atualiza a altura
    pA->height = Max(getHeight(pA->left), getHeight(pA->right)) + 1;
    pB->height = Max(getHeight(pB->left), getHeight(pB->right)) + 1;
    pC->height = Max(pA->height, pB->height) + 1;

    return pC;
}

tree *rotateAB(tree *subtree) {
    // Sub-arvore esquerda maior
    if (subtree->bal_fact > 1) {
        if (subtree->left->bal_fact > 0)
            subtree = LL(subtree);
        else 
            subtree = LR(subtree);
    }
    // Sub-arvore direita maior
    else if (subtree->bal_fact < -1) {
        if (subtree->right->bal_fact < 0)
            subtree = RR(subtree);
        else 
            subtree = RL(subtree);
    }

    return subtree;
}
// Operacoes
tree* insertAVL(tree *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value) 
        root->left = insertAVL(root->left, value);   
    else if (value > root->value) 
        root->right = insertAVL(root->right, value);
    
    // Corrige as alturas e fatores de balanceamento
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    root->height = Max(leftHeight, rightHeight) + 1;
    root->bal_fact = leftHeight - rightHeight;

    return rotateAB(root);
}

tree *removeAVL(tree *root, int value) {
    if (root == NULL)
        return root;

    if (value < root->value) 
        root->left = removeAVL(root->left, value);
    else if (value > root->value) 
        root->right = removeAVL(root->right, value);
    else { // Encontrou o no
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
    // Atualiza altura e fator de balanceamento
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    root->height = Max(leftHeight, rightHeight) + 1;
    root->bal_fact = leftHeight - rightHeight;

    return rotateAB(root);
}
// Busca
// int binSearch(tree *root, int value) {
//     if (root == NULL)
//         return 0;
//     else if (root->value == value)
//         return 1;
// 
//     if (value < root->value)
//         return binSearch(root->left, value);
//     else if (value > root->value)
//         return binSearch(root->right, value);
// }

// Impressao
void maxHeight(tree *root) {
    int he = getHeight(root->left) + 1;
    int hd = getHeight(root->right) + 1;
    printf("%d, %d, %d\n", root->height, he, hd);
}

void blackHeight(tree *root) {

}

void printChanges(tree *root) {
    
}

void freeTree(tree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
// IDEIAS: duas arvores, uma em AVL e outra em ARN
int main() {
    int num;
    tree *ARN = NULL;
    // Insere
    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        ARN = insertAVL(ARN, num);
    }

    freeTree(ARN);

    return 0;
}