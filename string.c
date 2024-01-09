#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "cstring.c"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_TYPE
#define STRING_TYPE
    #define ELEMENT_TYPE        char
    #define LIST_TYPE_NAME      String
    #define LIST_METHOD_PREFIX  str
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//STRING_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Derived Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_LIST_TYPE
#define STRING_LIST_TYPE
    #define ELEMENT_TYPE        String
    #define LIST_TYPE_NAME      StringList
    #define LIST_METHOD_PREFIX  strl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//STRING_LIST_TYPE

#ifndef STRING_LIST_LIST_TYPE
#define STRING_LIST_LIST_TYPE
    #define ELEMENT_TYPE        StringList
    #define LIST_TYPE_NAME      StringListList
    #define LIST_METHOD_PREFIX  strll
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//STRING_LIST_LIST_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Methods  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool str_is_null_terminated(String* s);
void str_null_terminate(String* s);
void str_un_null_terminate(String* s);

void    str_append(String* receiver, CString addme);
void    str_copy_from(String* dst, CString src);
String  str_init_as(CString src);

void str_print(String* s);
void str_println(String* s);

bool str_match_at(String* s, int index, CString pattern);

bool str_match_at(String* s, int index, CString pattern)
{
    if ( ! (0<=index && index<s->len) ) { return false; }

    while ( index!=s->len && *pattern ) {
        if ( s->data[index] != *pattern ) { return false; }
        ++index;
        ++pattern;
    }
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Method Implementations  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_METHODS
#define STRING_METHODS

String str_init_as(CString src)
{
    String s = str_init(8);
    str_copy_from(&s, src);
    return s;
}

inline
bool str_is_null_terminated(String* s)
{
    return ! str_is_empty(s) && *str_top(s)=='\0';
}

inline
void str_null_terminate(String* s)
{
    if ( ! str_is_null_terminated(s) ) { str_push(s, '\0'); }
}

inline
void str_un_null_terminate(String* s)
{
    if ( str_is_null_terminated(s) ) { str_pop(s); }
}

void str_print(String* s)
{
    str_null_terminate(s);
    printf("%s", s->data);
}

void str_println(String* s)
{
    str_print(s);
    printf("\n");
}

void str_append(String* receiver, CString addme)
{
    str_un_null_terminate(receiver);
    do {
        str_push(receiver, *addme);
    } while ( *(addme++) );
    str_null_terminate(receiver);
}

void str_copy_from(String* dst, CString src)
{
    dst->len=0;
    str_append(dst, src);
}

#endif//STRING_METHODS

