#include "cli.h"

#include <stdbool.h>

#include "../avl/avl.h"
#include "../avl/avl_handlers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


InputStatus readLine(char *buf, int maxLen) {
    if (fgets(buf, maxLen, stdin) == NULL) {
        // for startup.
        return INPUT_ERROR;
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    if (strcmp(buf, "reset") == 0) {
        return INPUT_RESET;
    }
    if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0) {
        return INPUT_QUIT;
    }
    return INPUT_OK;
}

InputStatus readInt(int *val) {
    char buf[128];
    const InputStatus status = readLine(buf, sizeof(buf));
    if (status != INPUT_OK) {
        return status;
    }
    char *endptr;
    const long lval = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        return INPUT_ERROR;
    }
    *val = (int) lval;
    return INPUT_OK;
}


void runCLI() {
    Node *root = NULL;
    char buf[256];

    printf("reset – быстрая очистка дерева; quit – выход из программы\n");
    printf("Команды (из ТЗ):\n");
    printf("  1 <key> <value> – Добавить / обновить узел\n");
    printf("  2 <key>         – Удалить узел\n");
    printf("  3               – Вывести дерево на экран\n");
    printf("  4 <key>         – Поиск значения по ключу\n");

    while (true) {
        printf(">>> ");
        const InputStatus status = readLine(buf, sizeof(buf));

        if (status == INPUT_QUIT) {
            printf("Пока-Пока!\n");
            break;
        }
        if (status == INPUT_RESET) {
            freeTree(root);
            root = NULL;
            printf("> Дерево очищено!\n");
            continue;
        }
        if (status == INPUT_ERROR) {
            printf("> [Ошибка] Ошибка ввода данных.\n");
            continue;
        }

        int op;
        char key[100];
        double val;
        const int parsed = sscanf(buf, "%d %99s %lf", &op, key, &val);

        if (parsed < 1) {
            printf("> [Ошибка] Неверный формат ввода\n");
            continue;
        }

        switch (op) {
            case OP_INSERT:
                root = handleInsert(root, parsed, key, val, stdout);
                break;
            case OP_DELETE:
                root = handleDelete(root, parsed, key, stdout);
                break;
            case OP_PRINT:
                handlePrint(root, stdout);
                break;
            case OP_SEARCH:
                handleSearch(root, parsed, key, stdout);
                break;
            default:
                printf("> [Ошибка] Неизвестная команда: %d\n", op);
                break;
        }
    }

    freeTree(root);
}
