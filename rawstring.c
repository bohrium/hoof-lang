#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "cstring.c"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef RAWSTRING_TYPE
#define RAWSTRING_TYPE
    #define ELEMENT_TYPE        char
    #define LIST_TYPE_NAME      RawString
    #define LIST_METHOD_PREFIX  rstr
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//RAWSTRING_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Derived Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef RAWSTRING_LIST_TYPE
#define RAWSTRING_LIST_TYPE
    #define ELEMENT_TYPE        RawString
    #define LIST_TYPE_NAME      RawStringList
    #define LIST_METHOD_PREFIX  rstrl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//RAWSTRING_LIST_TYPE

#ifndef RAWSTRING_LIST_LIST_TYPE
#define RAWSTRING_LIST_LIST_TYPE
    #define ELEMENT_TYPE        RawStringList
    #define LIST_TYPE_NAME      RawStringListList
    #define LIST_METHOD_PREFIX  rstrll
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//RAWSTRING_LIST_LIST_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Methods  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool rstr_is_null_terminated(RawString* s);
void rstr_unchecked_null_terminate(RawString* s);
void rstr_null_terminate(RawString* s);
void rstr_un_null_terminate(RawString* s);

void        rstr_append(RawString* receiver, CString addme);
void        rstr_copy_from(RawString* dst, CString src);
RawString   rstr_init_as(CString src);

void rstr_print(RawString* s);
void rstr_println(RawString* s);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Method Implementations  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef RAWSTRING_METHODS
#define RAWSTRING_METHODS

RawString rstr_init_as(CString src)
{
    RawString s = rstr_init(8);
    rstr_copy_from(&s, src);
    return s;
}

inline
bool rstr_is_null_terminated(RawString* s)
{
    return ! rstr_is_empty(s) && *rstr_top(s)=='\0';
}

inline
void rstr_unchecked_null_terminate(RawString* s)
{
    rstr_push(s, '\0');
}

inline
void rstr_null_terminate(RawString* s)
{
    if ( ! rstr_is_null_terminated(s) ) { rstr_push(s, '\0'); }
}

inline
void rstr_un_null_terminate(RawString* s)
{
    if ( rstr_is_null_terminated(s) ) { rstr_pop(s); }
}

void rstr_print(RawString* s)
{
    rstr_null_terminate(s);
    printf("%s", s->data);
}

void rstr_println(RawString* s)
{
    rstr_print(s);
    printf("\n");
}

void rstr_append(RawString* receiver, CString addme)
{
    rstr_un_null_terminate(receiver);
    do {
        rstr_push(receiver, *addme);
    } while ( *(addme++) );
    rstr_null_terminate(receiver);
}

void rstr_copy_from(RawString* dst, CString src)
{
    dst->len=0;
    rstr_append(dst, src);
}

#endif//RAWSTRING_METHODS

