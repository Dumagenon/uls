#include "libmx.h"

char *mx_strdup(const char *str)
{
    int len = mx_strlen(str);
    char *arr = mx_strnew(len);
    mx_strcpy(arr, str);
    return arr;
}
