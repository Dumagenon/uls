#include "libmx.h"

static bool strcmp_my(void *s1, void *s2) {
    return mx_strcmp(s1, s2) > 0 ? true : false;
}

void mx_sort_list(t_list *lst) {
    if (lst == NULL)
        return;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (t_list *tmp = lst; tmp->next; tmp = tmp->next)
        {
            if (strcmp_my(tmp->data, tmp->next->data))
            {
                char *temp = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = temp;
                int temp1 = tmp->len;
                tmp->len = tmp->next->len;
                tmp->next->len = temp1;
                flag = 1;
            }
        }
    }
}
