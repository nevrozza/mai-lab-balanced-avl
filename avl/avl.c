#include "avl.h"

#include <stdlib.h>
#include <string.h>

#include "avl_utils.h"

static Node *rightRotate(Node *y) {
    Node *x = y->l;
    Node *T2 = x->r;

    x->r = y;
    y->l = T2;

    y->height = max(getHeight(y->l), getHeight(y->r)) + 1;
    x->height = max(getHeight(x->l), getHeight(x->r)) + 1;

    return x;
}

static Node *leftRotate(Node *x) {
    Node *y = x->r;
    Node *T2 = y->l;

    y->l = x;
    x->r = T2;

    x->height = max(getHeight(x->l), getHeight(x->r)) + 1;
    y->height = max(getHeight(y->l), getHeight(y->r)) + 1;

    return y;
}

static Node *balanceNode(Node *node) {
    if (node == NULL) return NULL;

    node->height = 1 + max(getHeight(node->l), getHeight(node->r));
    const int balance = getHeight(node->l) - getHeight(node->r);

    if (balance > 1) {
        if (getHeight(node->l->l) < getHeight(node->l->r)) {
            node->l = leftRotate(node->l);
        }
        return rightRotate(node);
    }
    if (balance < -1) {
        if (getHeight(node->r->r) < getHeight(node->r->l)) {
            node->r = rightRotate(node->r);
        }
        return leftRotate(node);
    }

    return node;
}

Node *insert(Node *node, const char *key, double val, TreeResult *result) {
    if (node == NULL) {
        *result = RESULT_CREATED;
        return newNode(key, val);
    }

    const int cmp = strcmp(key, node->key);

    if (cmp < 0)
        node->l = insert(node->l, key, val, result);
    else if (cmp > 0)
        node->r = insert(node->r, key, val, result);
    else {
        node->val = val;
        *result = RESULT_UPDATED;
        return node;
    }

    return balanceNode(node);
}

Node *deleteNode(Node *node, const char *key, TreeResult *result) {
    if (node == NULL) {
        *result = RESULT_NOT_FOUND;
        return node;
    }

    const int cmp = strcmp(key, node->key);

    if (cmp < 0) {
        node->l = deleteNode(node->l, key, result);
    } else if (cmp > 0) {
        node->r = deleteNode(node->r, key, result);
    } else {
        *result = RESULT_DELETED;

        if (node->l == NULL || node->r == NULL) {
            Node *temp = node->l ? node->l : node->r;

            if (temp == NULL) {
                free(node);
                return NULL;
            }
            Node *toFree = node;
            node = temp;
            free(toFree);
        } else {
            const Node *temp = minValueNode(node->r);
            strcpy(node->key, temp->key);
            node->val = temp->val;
            node->r = deleteNode(node->r, temp->key, result);
        }
    }

    return balanceNode(node);
}

Node *search(Node *node, const char *key, TreeResult *result) {
    if (node == NULL) {
        *result = RESULT_NOT_FOUND;
        return NULL;
    }

    int cmp = strcmp(key, node->key);

    if (cmp == 0) {
        return node;
    }
    if (cmp < 0) {
        return search(node->l, key, result);
    }

    return search(node->r, key, result);
}
