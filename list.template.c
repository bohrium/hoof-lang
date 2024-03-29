#include "stdbool.h"
#include "stdlib.h"

#include "preprocessor_tricks.h"

//#include "list.template.h"

#define ELT ELEMENT_TYPE
#define LMP LIST_METHOD_PREFIX
#define LTN LIST_TYPE_NAME

#define _INIT           CONCAT(LMP, _init)
#define _FREE           CONCAT(LMP, _free)
#define _RESIZE         CONCAT(LMP, _resize)
#define __UNSAFE_COPY   CONCAT(LMP, __unsafe_copy)
#define _LEN            CONCAT(LMP, _len)
#define _IS_EMPTY       CONCAT(LMP, _is_empty)
#define _IS_FULL        CONCAT(LMP, _is_full)

#define _PUSH_UNSAFE    CONCAT(LMP, _push_unsafe)
#define _POP_UNSAFE     CONCAT(LMP, _pop_unsafe)
#define _TOP_UNSAFE     CONCAT(LMP, _top_unsafe)
#define _GETREF_UNSAFE  CONCAT(LMP, _getref_unsafe)

#define _PUSH   CONCAT(LMP, _push)
#define _POP    CONCAT(LMP, _pop)
#define _TOP    CONCAT(LMP, _top)
#define _GETREF CONCAT(LMP, _getref)



/* ========================================================================= */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Implementation  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -----  memory management  ----------------------------------------------- */

inline
LTN _INIT(int cap)
{
    return (LTN){
        (ELT*) malloc(sizeof(ELT)*cap),
        0,
        cap
    };
}

inline
void _FREE(LTN* list)
{
    free(list->data);
    *list = (LTN){NULL, 0, 0};
}

// declare before define because inline
void __UNSAFE_COPY(ELT const* restrict src, ELT const* src_end, ELT*restrict dst);

inline
void __UNSAFE_COPY(ELT const* restrict src, ELT const* src_end, ELT*restrict dst)
{
    while (src != src_end) { *(dst++) = *(src++); }
}


void _RESIZE(LTN* list, int cap)
{
    if ( ! (list->len < cap) ) { return; }
    ELT* data = malloc(sizeof(ELT)*cap);
    { /* COPY */
#if 0
        for (int i = 0; i != list->len; ++i) { data[i] = list->data[i]; }
#else
        // the `restrict` keywords speeds the copy up by about 20% (in our
        // tests that pre-stretch-out the malloc part) but one expects that in
        // real life, the malloc can often overwhelm.
        __UNSAFE_COPY(list->data, list->data + list->len, data);
#endif
    }
    free(list->data);
    *list = (LTN){data, list->len, cap};
}

inline
int _LEN(LTN const* list)
{
    return list->len;
}

inline
bool _IS_EMPTY(LTN const* list)
{
    return list->len == 0;
}

inline
bool _IS_FULL(LTN const* list)
{
    return list->len == list->cap;
}

/* -----  unsafe accessors (no expanding, no bounds checks)  --------------- */

inline
void _PUSH_UNSAFE(LTN* list, ELT el)
{
    list->data[list->len] = el;
    ++list->len;
}

inline
ELT* _POP_UNSAFE(LTN* list)
{
    --(list->len);
    return &(list->data[list->len]);
}

inline
ELT* _TOP_UNSAFE(LTN const* list)
{
    return &(list->data[list->len-1]);
}

inline
ELT* _GETREF_UNSAFE(LTN const* list, int index)
{
    return &(list->data[index]);
}

/* -----  safe accessors (expand or return NULL as needed)  ---------------- */

void _PUSH(LTN* list, ELT el)
{
    if ( _IS_FULL(list) ) { _RESIZE(list, 1 + EXPAND_FACTOR*list->cap); }
    _PUSH_UNSAFE(list, el);
}

inline
ELT* _POP(LTN* list)
{
    if ( _IS_EMPTY(list) ) { return NULL; }
    return _POP_UNSAFE(list);
}

inline
ELT* _TOP(LTN const* list)
{
    if ( _IS_EMPTY(list) ) { return NULL; }
    return _TOP_UNSAFE(list);
}

inline
ELT* _GETREF(LTN const* list, int index)
{
    if ( ! ( 0<=index && index<list->len) ) { return NULL; }
    return _GETREF_UNSAFE(list, index);
}



/* ========================================================================= */



#undef ELT
#undef LMP
#undef LTN

#undef _INIT
#undef _FREE
#undef _RESIZE
#undef _LEN
#undef _IS_EMPTY
#undef _IS_FULL

#undef _PUSH_UNSAFE
#undef _POP_UNSAFE
#undef _TOP_UNSAFE
#undef _GETREF_UNSAFE

#undef _PUSH
#undef _POP
#undef _TOP
#undef _GETREF


