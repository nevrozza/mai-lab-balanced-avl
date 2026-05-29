#include "avl_utils.h"

#include <stdbool.h>

#include "../utils/utils.h"


#include <stdlib.h>
#include <string.h>


static void printTreeHelper(Node *root, char *prefix, const bool isLeft, const bool isRoot, FILE *out) {
    if (root == NULL) return;

    fprintf(out, "%s", prefix);

    if (!isRoot) {
        fprintf(out, "%s", isLeft ? "├── L: " : "└── R: ");
    } else {
        fprintf(out, "ROOT: ");
    }

    fprintf(out, "%s (%.2f)\n", root->key, root->val);

    char newPrefix[512];
    if (!isRoot) {
        snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "│   " : "    ");
    } else {
        snprintf(newPrefix, sizeof(newPrefix), "%s", prefix);
    }

    if (root->l || root->r) {
        printTreeHelper(root->l, newPrefix, true, false, out);
        printTreeHelper(root->r, newPrefix, false, false, out);
    }
}

void printTree(Node *root, FILE *out) {
    char prefix[512] = "";
    printTreeHelper(root, prefix, false, true, out);
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


int getHeight(const Node *node) {
    if (node == NULL) return 0;
    return node->height;
}

int max(const int a, const int b) {
    return a > b ? a : b;
}
