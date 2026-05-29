#include "parser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../avl/avl.h"
#include "../avl/avl_utils.h"
#include "../utils/utils.h"


typedef enum {
    OP_INSERT = 1,
    OP_DELETE = 2,
    OP_PRINT = 3,
    OP_SEARCH = 4
} OperationType;

static bool isKeyValid(const char *key) {
    const int len = strlen(key);
    if (len == 0 || len >= MAX_KEY_LEN) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha((unsigned char) key[i])) return false;
    }
    return true;
}


static Node *handleInsert(Node *node, const int parsed, const char *key, const double val, FILE *out) {
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

static Node *handleDelete(Node *node, const int parsed, const char *key, FILE *out) {
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

static void handleSearch(Node *node, const int parsed, const char *key, FILE *out) {
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

static void handlePrint(Node *node, FILE *out) {
    fprintf(out, "> Дерево:\n");
    if (node == NULL) {
        fprintf(out, "  пустое =/\n");
    } else {
        printTree(node, out);
        fprintf(out, "\n");
    }
}

void processCommands(const char *inputFilename, const char *outputFilename) {
    Node *root = NULL;
    FILE *in = fopen(inputFilename, "r");
    FILE *out = fopen(outputFilename, "w");

    if (!in) {
        softError("Не удалось открыть input-файл");
        return;
    }
    if (!out) {
        softError("Не удалось открыть output-файл");
        fclose(in);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), in)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        fprintf(out, "%s\n", line);

        int op;
        char key[100] = {0};
        double val = 0.0;

        const int parsed = sscanf(line, "%d %s %lf", &op, key, &val);

        if (parsed < 1) {
            continue;
        }

        switch (op) {
            case OP_INSERT:
                root = handleInsert(root, parsed, key, val, out);
                break;
            case OP_DELETE:
                root = handleDelete(root, parsed, key, out);
                break;
            case OP_PRINT:
                handlePrint(root, out);
                break;
            case OP_SEARCH:
                handleSearch(root, parsed, key, out);
                break;
            default:
                fprintf(out, "> [Ошибка] Неизвестная команда\n");
                break;
        }
        fprintf(out, "------------------------\n");
    }

    freeTree(root);
    fclose(in);
    fclose(out);
}
