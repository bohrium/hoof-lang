#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "preprocessor_tricks.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Basic Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef CSTRING_TYPE
#define CSTRING_TYPE
    typedef char const* CString;
#endif//CSTRING_TYPE

#ifndef CSTRING_LIST_TYPE
#define CSTRING_LIST_TYPE
    #define ELEMENT_TYPE        CString
    #define LIST_TYPE_NAME      CStringList
    #define LIST_METHOD_PREFIX  cstrl
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//CSTRING_LIST_TYPE

#ifndef CSTRING_LIST_LIST_TYPE
#define CSTRING_LIST_LIST_TYPE
    #define ELEMENT_TYPE        CStringList
    #define LIST_TYPE_NAME      CStringListList
    #define LIST_METHOD_PREFIX  cstrll
    #define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
    #include "list.template.c"
    #undef ELEMENT_TYPE
    #undef LIST_TYPE_NAME
    #undef LIST_METHOD_PREFIX
    #undef EXPAND_FACTOR
#endif//CSTRING_LIST_LIST_TYPE

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Methods  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef CSTRING_METHODS
#define CSTRING_METHODS

int cstr_len(CString s)
{
    char const* it = s;
    while ( *it ) { ++it; }
    return it-s;
}

bool cstr_match_substring(CString s, CString pattern)
{
    while ( *pattern ) {
        // if ( ! *s ) { return false; }// un-needed due to null termination
        if ( *s != *pattern ) { return false; }
        ++s;
        ++pattern;
    }
    return true;
}

#endif//CSTRING_METHODS

