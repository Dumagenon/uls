#include "libmx.h"

void mx_push_back(t_list **list, char *data, int len) {
    if (*list == NULL) {
        t_list *node = mx_create_node(data, len);
        *list = node;
    } else {
        t_list *node = mx_create_node(data, len), *p = *list;
        while (p->next)
            p = p->next;
        p->next = node;
    }
}
