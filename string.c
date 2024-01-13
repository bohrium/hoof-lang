#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "cstring.h"
#include "rawstring.h"
#include "string.h"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Derived Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

//#ifndef STRING_LIST_TYPE
//#define STRING_LIST_TYPE
    #define ELEMENT_TYPE        String
    #define LIST_TYPE_NAME      StringList
    //#pragma message(STRING( LIST_TYPE_NAME ))
    #define LIST_METHOD_PREFIX  strl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
//#endif//STRING_LIST_TYPE

//#ifndef STRING_LIST_LIST_TYPE
//#define STRING_LIST_LIST_TYPE
    #define ELEMENT_TYPE        StringList
    #define LIST_TYPE_NAME      StringListList
    #define LIST_METHOD_PREFIX  strll
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
//#endif//STRING_LIST_LIST_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Method Implementations  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_METHODS_BASIC
#define STRING_METHODS_BASIC

/* -----  memory and chunkwise  -------------------------------------------- */

String str_init(int cap)
{
    // TODO : resize to cap(+1)
    // return CAST_AS(String, rstr_init_as(""));
    return CAST_AS(String, { rstr_init_as("") });
}

String str_init_as(CString src)
{
    return CAST_AS(String, { rstr_init_as(src) } );
}

inline
int str_len(String const* s)
{
    RawString const* raw = &(s->raw); //CAST_AS(RawString const*, &(s.raw));
    return rstr_len(raw)-1;
}

void str_free(String* s)
{
    RawString* raw = &(s->raw); //CAST_AS(RawString*, s);
    rstr_free(&(s->raw));
}

/* -----  character-wise  -------------------------------------------------- */

inline
void str_push(String* s, char c)
// assumes c!='\0'
{
    RawString* raw = &(s->raw); //CAST_AS(RawString*, s);
    int last_occupied = rstr_len(raw)-1;
    *rstr_getref_unsafe(raw, last_occupied ) = c;
    rstr_unchecked_null_terminate(raw);
}

inline
char str_top(String const* s)
{
    RawString const* raw = &(s->raw); //CAST_AS(RawString const*, s);
    int last_occupied = rstr_len(raw)-1;
    return *rstr_getref_unsafe(raw, last_occupied - 1);
}

inline
char str_pop(String* s)
{
    RawString* raw = &(s->raw); //CAST_AS(RawString*, s);
    if ( rstr_len(raw) == 1 ) { return '\0'; }
    char c = str_top(s);
    { /* ATTN : order matters */
        rstr_pop(raw);
        *rstr_getref_unsafe(raw, rstr_len(raw)-1) = '\0';
    }
    return c;
}

inline
char str_at(String const* s, int index)
// does not check index bounds
{
    RawString const* raw = &(s->raw); //CAST_AS(RawString const*, s);
    return *rstr_getref_unsafe(raw, index);
}

/* -----  chunk-wise  ------------------------------------------------------ */

void str_append(String* receiver, CString addme)
{
    RawString* raw = &(receiver->raw); //CAST_AS(RawString*, receiver);
    rstr_un_null_terminate(raw); // TODO: make unchecked
    do {
        rstr_push(raw, *addme);
    } while ( *(addme++) );
    rstr_unchecked_null_terminate(raw);
}

void str_copy_from(String* dst, CString src)
{
    dst->raw.len=0;
    str_append(dst, src);
}

/* -----  display  --------------------------------------------------------- */

void str_print(String const* s)
{
    printf("%s", s->raw.data);
}

void str_println(String const* s)
{
    str_print(s);
    printf("\n");
}

#endif//STRING_METHODS_BASIC

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Text Processing Operations  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRING_METHODS_TEXT
#define STRING_METHODS_TEXT

bool str_match_at(String const* s, int index, CString pattern)
{
    if ( ! (0<=index && index < s->raw.len) ) { return false; }

    while ( index!=s->raw.len && *pattern ) {
        if ( str_at(s, index) != *pattern ) { return false; }
        ++index;
        ++pattern;
    }

    if ( *pattern ) { return false; } // reject if matched only *part* of
                                      // pattern (since we assume `s` is
                                      // null-terminated, this line of code
                                      // isn't actually needed)

    return true;
}

#endif//STRING_METHODS_TEXT
