#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "preprocessor_tricks.h"

#ifndef INT_LIST_TYPE
#define INT_LIST_TYPE
    #define ELEMENT_TYPE        int
    #define LIST_TYPE_NAME      IntList
    #define LIST_METHOD_PREFIX  il
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//INT_LIST_TYPE

#ifndef INT_LIST_LIST_TYPE
#define INT_LIST_LIST_TYPE
    #define ELEMENT_TYPE        IntList
    #define LIST_TYPE_NAME      IntListList
    #define LIST_METHOD_PREFIX  ill
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//INT_LIST_LIST_TYPE

#ifndef INT_PTR_LIST_TYPE
#define INT_PTR_LIST_TYPE
    #define ELEMENT_TYPE        int*
    #define LIST_TYPE_NAME      IntPtrList
    #define LIST_METHOD_PREFIX  ipl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//INT_PTR_LIST_TYPE

