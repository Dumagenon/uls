#include "libmx.h"

void mx_printint(int n)
{
    long int i = n;
    int v = 1;
    if (n < 0)
    {
        mx_printchar('-');
        i *= -1;
    }
    while (i / v >= 10)
        v *= 10;
    while (v > 0)
    {
        mx_printchar((i / v) % 10 + '0');
        v /= 10;
    }
}
