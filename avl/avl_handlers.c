#include "avl_handlers.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static bool isKeyValid(const char *key) {
    const int len = strlen(key);
    if (len == 0 || len >= MAX_KEY_LEN) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha((unsigned char) key[i])) return false;
    }
    return true;
}

Node *handleInsert(Node *node, const int parsed, const char *key, const double val, FILE *out) {
    if (parsed != 3) {
        fprintf(out, "> [Ошибка] Неверный синтаксис (ожидается: 1 <ключ> <значение>)\n");
        return node;
    }
    if (!isKeyValid(key)) {
        fprintf(out, "> [Ошибка] Неверный формат ключа\n");
        return node;
    }

    TreeResult result = RESULT_NOT_FOUND;
    node = insert(node, key, val, &result);

    if (result == RESULT_CREATED) {
        fprintf(out, "> Успешно добавлено\n");
    } else if (result == RESULT_UPDATED) {
        fprintf(out, "> Значение ключа обновлено\n");
    }
    return node;
}

Node *handleDelete(Node *node, const int parsed, const char *key, FILE *out) {
    if (parsed != 2) {
        fprintf(out, "> [Ошибка] Неверный синтаксис (ожидается: 2 <ключ>)\n");
        return node;
    }

    TreeResult result = RESULT_NOT_FOUND;
    node = deleteNode(node, key, &result);

    if (result == RESULT_DELETED) {
        fprintf(out, "> Узел удален\n");
    } else {
        fprintf(out, "> Ключ не найден\n");
    }
    return node;
}

void handleSearch(Node *node, const int parsed, const char *key, FILE *out) {
    if (parsed != 2) {
        fprintf(out, "> [Ошибка] Неверный синтаксис (ожидается: 4 <ключ>)\n");
        return;
    }

    TreeResult result = RESULT_NOT_FOUND;
    const Node *res = search(node, key, &result);

    if (res != NULL) {
        fprintf(out, "> Найдено, значение = %lf\n", res->val);
    } else {
        fprintf(out, "> Ключ не найден\n");
    }
}

void handlePrint(Node *node, FILE *out) {
    fprintf(out, "> Дерево:\n");
    if (node == NULL) {
        fprintf(out, "  пустое =/\n");
    } else {
        printTree(node, out);
        fprintf(out, "\n");
    }
}
