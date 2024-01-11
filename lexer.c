#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "list.c"
#include "cstring.c"
#include "string.c"

int main()
{
    printf("hi!\n");
    String s = str_init_as(
      "woah!                                                        \n"
      "woah!                                                        \n"
      "woah!                                                        \n"
      "woah!                                                        \n"
      "woah!                                                        \n"
      "woah!                                                        \n"
    );
    str_print(&s);

    str_free(&s);
    printf("bye!\n");
}
