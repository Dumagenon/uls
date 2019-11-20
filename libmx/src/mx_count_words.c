#include "libmx.h"

int mx_count_words(const char *str, char c)
{
    if (str == NULL)
        return -1;
    int res = 0, state = 0;
    while (*str)
    {
        if (*str == c)
            state = 0;
        else if (state == 0)
        {
            state = 1;
            res++;
        }
        str++;
    }
    return res;
}
