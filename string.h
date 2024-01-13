#ifndef STRING_H
#define STRING_H

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "cstring.h"
#include "rawstring.h"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// ATTN: strings are necessarily null-terminated at all times
//
//
//

// NOTE : ensures no implicit casting!
typedef struct { RawString raw; } String;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Derived Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_LIST_TYPE
#define STRING_LIST_TYPE
    #define ELEMENT_TYPE        String
    #define LIST_TYPE_NAME      StringList
    #define LIST_METHOD_PREFIX  strl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.h"
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
    #include "list.template.h"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//STRING_LIST_LIST_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Methods  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -----  basic : memory and chunk-wise  ----------------------------------- */

String  str_init(int cap);
int str_len(String const* s);
void str_free(String* s);

String  str_init_as(CString src);
void    str_append(String* receiver, CString addme);
void    str_copy_from(String* dst, CString src);

/* -----  basic : character-wise ------------------------------------------- */

// ATTN: if string is empty, returns '\0'
char str_at(String const* s, int index);    // does not check index bounds
char str_top(String const* s);
char str_pop(String* s);
void str_push(String* s, char c);           // assumes c!='\0'

/* -----  basic : display  ------------------------------------------------- */

void str_print(String const* s);
void str_println(String const* s);

/* -----  text processing -------------------------------------------------- */

bool str_match_at(String const* s, int index, CString pattern);

#endif//STRING_H
