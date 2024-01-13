#ifndef RAWSTRING_H
#define RAWSTRING_H

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "cstring.h"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef RAWSTRING_TYPE
#define RAWSTRING_TYPE
    #define ELEMENT_TYPE        char
    #define LIST_TYPE_NAME      RawString
    #define LIST_METHOD_PREFIX  rstr
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.h"
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
    #include "list.template.h"
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
    #include "list.template.h"
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

#endif//RAWSTRING_H
