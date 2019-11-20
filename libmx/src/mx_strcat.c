#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2)
{
    char *temp = s1;
    while (*s1)
        s1++;
    while (*s2)
        *s1++ = *s2++;
    *s1 = '\0';
    return temp;
}
// int main() {
//     char ar[] = "Hello ", arr[] = "world!";
//     printf("%s", mx_strcat(ar, arr));
//     return 0;
// }
