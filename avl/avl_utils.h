#ifndef AVL_AVL_UTILS_H
#define AVL_AVL_UTILS_H
#include "avl.h"
#include <stdio.h>


void printTree(Node *root, int space, FILE *out);


Node *newNode(const char *key, double val);


int getBalance(const Node *node);

Node *minValueNode(Node *node);

void freeTree(Node *node);

int getHeight(const Node *node);


int max(int a, int b);

#endif //AVL_AVL_UTILS_H
