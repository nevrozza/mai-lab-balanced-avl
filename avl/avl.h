#ifndef AVL_AVL_H
#define AVL_AVL_H

#define MAX_KEY_LEN 7

typedef struct Node {
    char key[MAX_KEY_LEN];
    double val;
    struct Node *l;
    struct Node *r;
    int height;
} Node;


typedef enum {
    RESULT_NOT_FOUND, // [Поиск/Удаление] Узел не найден
    RESULT_CREATED, //   [Вставка] Новый узел успешно создан
    RESULT_UPDATED, //   [Вставка] Значение существующего узла обновлено
    RESULT_DELETED //    [Удаление] Узел успешно удален
} TreeResult;

Node *insert(Node *node, const char *key, double val, TreeResult *result);

Node *deleteNode(Node *node, const char *key, TreeResult *result);

Node *search(Node *node, const char *key, TreeResult *result);
#endif //AVL_AVL_H
