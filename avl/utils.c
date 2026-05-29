#include "utils.h"

#include <c++/v1/cstdlib>


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

    return;
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
