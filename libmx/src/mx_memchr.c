#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char  *str = (unsigned char*)s;

    for(size_t i = 0; *str != (unsigned char)c && i < n; i++, str++);

    if(*str == c) return str;
    
    return NULL;
}

// int main (void)
// {
//     // Исходный массив
//     unsigned char src[15]="1234567890";
//     // Переменная, в которую будет сохранен указатель
//     // на искомый символ.
//     char *sym;
//     // Вывод исходного массива
//     printf ("src old: %s\n",src);

//     // Поиск требуемого символа
//     sym = mx_memchr (src, '4', 20);

//     // Если требуемый символ найден, то заменяем его
//     // на символ '!'
//     if (sym != NULL)
//         sym[0]='!';

//     // Вывод исходного массива
//     printf ("src new: %s\n",sym);

//     return 0;
// }
