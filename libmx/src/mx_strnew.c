#include "libmx.h"

char *mx_strnew(const int size)
{
    if (size < 0)
        return NULL;
    char *arr = (char *)malloc(sizeof(char) * size + 1);
    if (arr == NULL)
        return NULL;

    for (int i = 0; i <= size; i++)
    {
        arr[i] = '\0';
    }
    return arr;
}
