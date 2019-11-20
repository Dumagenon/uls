#include "libmx.h"

t_list *mx_create_node(char *data, int len) {
    t_list *node = (t_list *)malloc(sizeof(t_list));
    if (node == NULL)
        return NULL;

    node->data = data;
    node->len = len;
    node->next = NULL;

    return node;
}
