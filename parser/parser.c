#include "parser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../avl/avl.h"
#include "../avl/avl_utils.h"
#include "../utils/utils.h"


static bool isKeyValid(const char *key) {
    const int len = strlen(key);
    if (len == 0 || len >= MAX_KEY_LEN) return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha((unsigned char) key[i])) return false;
    }
    return true;
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
        TreeResult result;

        switch (op) {
            case 1: // Insert
                if (parsed == 3) {
                    if (isKeyValid(key)) {
                        result = RESULT_NOT_FOUND;
                        root = insert(root, key, val, &result);

                        if (result == RESULT_CREATED) {
                            fprintf(out, "> Успешно добавлено\n");
                        } else if (result == RESULT_UPDATED) {
                            fprintf(out, "> Значение ключа обновлено\n");
                        }
                    } else {
                        fprintf(out, "> [Ошибка] Неверный формат ключа\n");
                    }
                } else {
                    fprintf(out, "> [Ошибка] Неверный синтаксис\n");
                }
                break;

            case 2: // Delete
                if (parsed == 2) {
                    result = RESULT_NOT_FOUND;
                    root = deleteNode(root, key, &result);

                    if (result == RESULT_DELETED) {
                        fprintf(out, "> Узел удален\n");
                    } else {
                        fprintf(out, "> Ключ не найден\n");
                    }
                } else {
                    fprintf(out, "> [Ошибка] Неверный синтаксис\n");
                }
                break;

            case 3: // Print tree
                fprintf(out, "> Дерево:\n");
                if (root == NULL) {
                    fprintf(out, "  пустое =/\n");
                } else {
                    printTree(root, out);
                    fprintf(out, "\n");
                }
                break;

            case 4: // Search
                if (parsed == 2) {
                    result = RESULT_NOT_FOUND;
                    const Node *res = search(root, key, &result);

                    if (res != NULL) {
                        fprintf(out, "> Найдено, значение = %lf\n", res->val);
                    } else {
                        fprintf(out, "> Ключ не найден\n");
                    }
                } else {
                    fprintf(out, "> [Ошибка] Неверный синтаксис\n");
                }
                break;

            default: // Unknown
                fprintf(out, "> [Ошибка] Неизвестная команда\n");
                break;
        }
        fprintf(out, "------------------------\n");
    }

    freeTree(root);
    fclose(in);
    fclose(out);
}
