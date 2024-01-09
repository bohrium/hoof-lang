#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define ELEMENT_TYPE        int
#define LIST_TYPE_NAME      IntList
#define LIST_METHOD_PREFIX  il
#define EXPAND_FACTOR       1.618
#include "list.c"
#undef ELEMENT_TYPE
#undef LIST_TYPE_NAME
#undef LIST_METHOD_PREFIX
#undef EXPAND_FACTOR

int main()
{
    printf("hi!\n");
    IntList ily = il_init(5);

    for (int i = 0; i != 20; ++i) {
        il_push(&ily, i);
        printf("%d %d!\n", ily.len, ily.cap);
    }
    il_free(&ily);

    printf("bye!\n");
    return 0;
}
