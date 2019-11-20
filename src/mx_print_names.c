#include "uls.h"

int max_name_len(t_list *list)
{
    int max = 0;
    for (t_list *i = list; i != NULL; i = i->next)
        if (i->len > max)
            max = i->len;
    return max;
}

char **array_of_names(t_list *list, int size)
{
    char **res = (char **)malloc(sizeof(char *) * (size + 1));
    int i = 0;
    for (t_list *j = list; j != NULL; j = j->next, i++)
        res[i] = mx_strdup(j->data);
    res[size] = NULL;
    return res;
}

void print_spaces(int num)
{
    for (int d = 0; d <= num; d++)
    {
        mx_printchar(' ');
    }
}

void print_names(char **names, int max, int rows, int size)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i + j < size; j += rows)
        {
            if (mx_strlen(names[i + j]) < max)
            {
                mx_printstr(names[i + j]);
                print_spaces(max - mx_strlen(names[i + j]));
            }
            else
            {
                mx_printstr(names[i + j]);
                mx_printchar(' ');
            }
        }
        mx_printchar('\n');
    }
}
