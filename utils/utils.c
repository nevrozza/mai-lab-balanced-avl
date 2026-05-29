#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void fatalError(char msg[]) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void softError(const char msg[]) {
    // было stderr, но проблемы с CLI
    fprintf(stdout, "Ошибка: %s", msg);
}

void fatalMemoryError() {
    fatalError("MemoryError");
}
