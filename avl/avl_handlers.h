#ifndef AVL_AVL_HANDLERS_H
#define AVL_AVL_HANDLERS_H

#include "avl.h"
#include "avl_utils.h"


typedef enum {
    OP_INSERT = 1,
    OP_DELETE = 2,
    OP_PRINT = 3,
    OP_SEARCH = 4
} OperationType;

Node *handleInsert(Node *node, int parsed, const char *key, double val, FILE *out);

Node *handleDelete(Node *node, int parsed, const char *key, FILE *out);

void handleSearch(Node *node, int parsed, const char *key, FILE *out);

void handlePrint(Node *node, FILE *out);
#endif //AVL_AVL_HANDLERS_H
