#include "libmx.h"

bool mx_isalpha(int c) {
  if ((c >= '\101' && c <= '\132') || (c >= '\141' && c <= '\176')) 
    return 1;
  else return 0;
}
