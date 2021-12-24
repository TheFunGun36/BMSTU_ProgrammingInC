#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mylib.h"
#include "exit_code.h"

int main(int argc, char *argv[])
{
   char str1[] = "aboba";
   char str2[] = "klass";

   char str[256];
   int ret = my_snprintf(str, 18, "%s, bobiba, %s", str1, str2);

   printf("%d, |%s|", ret, str);

    return 0;
}
