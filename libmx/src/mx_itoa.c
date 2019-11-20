#include "libmx.h"

char *mx_itoa(int number)
{
    char *res;
    if (number != 0)
    {
        long int num = number;
        int flag = 0;
        if (num < 0)
        {
            num *= -1;
            flag = 1;
        }

        int len = 0;
        for (long int i = num; i > 0; i /= 10)
            len++;

        if (flag)
        {
            res = mx_strnew(len + 1);
            res[0] = '-';
            while (num > 0)
            {
                res[len] = num % 10 + '0';
                num /= 10;
                len--;
            }
        }
        else
        {
            res = mx_strnew(len);
            while (num > 0)
            {
                len--;
                res[len] = num % 10 + '0';
                num /= 10;
            }
        }
    }
    else
    {
        res = malloc(2);
        res[0] = '0';
        res[1] = '\0';
    }
    return res;
}
