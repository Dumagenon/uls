#include "libmx.h"

char **mx_strsplit(const char *s, char c)
{
  if (s == NULL)
    return NULL;

  int count = mx_count_words(s, c),
      len = mx_strlen(s), indexDel, indexArr = 0;
  char **res = (char **)malloc(sizeof(char *) * (count + 1));
  res[count] = NULL;

  if (count == 1)
  {
    res[0] = mx_strdup(s);
    return res;
  }
  else
  {
    for (int i = 0; i < len; i++)
    {
      indexDel = mx_get_char_index(s, c);
      indexDel = indexDel == -1 ? mx_strlen(s) : indexDel;

      if (indexDel)
      {
        res[indexArr] = mx_strndup(s, indexDel);
        s += mx_strlen(res[indexArr]) - 1;
        i += mx_strlen(res[indexArr]) - 1;
        indexArr++;
      }
      s++;
    }
  }
  return res;
}
