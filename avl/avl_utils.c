#include "avl_utils.h"
#include "../utils/utils.h"


#include <stdlib.h>
#include <string.h>


void printTree(Node *root, int space, FILE *out) {
    if (root == NULL) return;
    const int COUNT = 7;
    space += COUNT;

    printTree(root->r, space, out);

    fprintf(out, "\n");
    for (int i = COUNT; i < space; i++)
        fprintf(out, " ");
    fprintf(out, "%s (%.2f)\n", root->key, root->val);

    printTree(root->l, space, out);
}

Node *newNode(const char *key, const double val) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        fatalMemoryError();
    }
    strcpy(node->key, key);
    node->val = val;
    node->l = NULL;
    node->r = NULL;
    node->height = 1;
    return node;
}

int getBalance(const Node *node) {
    if (node == NULL) return 0;
    return getHeight(node->l) - getHeight(node->r);
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->l != NULL)
        current = current->l;
    return current;
}


void freeTree(Node *node) {
    if (node != NULL) {
        freeTree(node->l);
        freeTree(node->r);
        free(node);
    }
}


int getHeight(Node *node) {
    if (node == NULL) return 0;
    return node->height;
}

int max(const int a, const int b) {
    return a > b ? a : b;
}
