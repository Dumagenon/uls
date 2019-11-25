#include "uls.h"

static bool strcmp_my(void *s1, void *s2)
{
    return mx_strcmp(s1, s2) > 0 ? true : false;
}

void sort(t_str *lst)
{
    if (lst == NULL)
        return;
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (t_str *tmp = lst; tmp->next; tmp = tmp->next)
        {
            if (strcmp_my(tmp->data[8], tmp->next->data[8]))
            {
                char **temp = tmp->data;
                tmp->data = tmp->next->data;
                tmp->next->data = temp;
                flag = 1;
            }
        }
    }
}
