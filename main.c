#include <stdbool.h>
#include <stdio.h>

#include "cli/cli.h"
#include "parser/parser.h"

int main() {
    processCommands("/Users/nevrozq/Code/C/avl/input.txt", "/Users/nevrozq/Code/C/avl/output.txt");
    printf("\n");
    runCLI();
}
