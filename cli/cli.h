#ifndef AVL_CLI_H
#define AVL_CLI_H

typedef enum {
    INPUT_OK,
    INPUT_RESET,
    INPUT_QUIT,
    INPUT_ERROR
} InputStatus;

InputStatus readLine(char *buf, int maxLen);

InputStatus readInt(int *val);


void runCLI();

#endif //AVL_CLI_H
