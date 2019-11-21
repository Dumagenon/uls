#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
    unsigned char *str = NULL;
    for (str = (unsigned char *)s + n;
         n > 0 && *str != (unsigned char)c;
         n--, str--);

    if (*str == c)
        return str;

    return NULL;
}

// int main (void)
// {
//    // Исходный массив
//    char src[] = "Trinity";
//    // Переменная, в которую будет сохранен указатель
//    // на искомый символ.
//    char *sym;

//    // Вывод исходного массива
//    printf ("src old: %s\n",src);

//    // Поиск требуемого символа
//    sym = mx_memrchr(src, 'i', 3);

//    // Вывод исходного массива
//    printf ("src new: %s\n", sym);

//    return 0;
// }
