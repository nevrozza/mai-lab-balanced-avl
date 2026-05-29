#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../avl/avl.h"
#include "../avl/avl_utils.h"
#include "../avl/avl_handlers.h"
#include "../utils/utils.h"


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

    printf("%s был обработан (вывод: %s)", inputFilename, outputFilename);
}
