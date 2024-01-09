#include "stdlib.h"
#include "stdbool.h"

#define ELT ELEMENT_TYPE
#define LMP LIST_METHOD_PREFIX
#define LTN LIST_TYPE_NAME



/* ========================================================================= */



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Interface  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -----  pre-requisites  -------------------------------------------------- */

// ATTN the following macros must already be defined
#if    ! defined(ELEMENT_TYPE      ) /* type  */  \
    || ! defined(LIST_TYPE_NAME    ) /* ident */  \
    || ! defined(LIST_METHOD_PREFIX) /* ident */  \
    || ! defined(EXPAND_FACTOR     ) /* float */
  #error
#endif

/* -----  type and method declarations  ------------------------------------ */

typedef struct LTN LTN;

// memory management:
LTN     LTN##_init      (int cap);
void    LTN##_free      (LTN* list);
void    LTN##_resize    (LTN* list, int cap);
int     LTN##_len       (LTN const* list);
bool    LTN##_is_empty  (LTN const* list);
bool    LTN##_is_full   (LTN const* list);

// unsafe accessors (no expanding, no bounds checks):
void    LTN##_push_unsafe   (LTN* list, (ELT) el);
*(ELT)  LTN##_pop_unsafe    (LTN* list);
*(ELT)  LTN##_top_unsafe    (LTN void* list);
*(ELT)  LTN##_getref_unsafe (LTN const* list, int index);

// safe accessors (expand or return NULL as needed)
void    LTN##_push  (LTN* list, (ELT) el);
*(ELT)  LTN##_pop   (LTN* list);
*(ELT)  LTN##_top   (LTN const* list);
*(ELT)  LTN##_getref(LTN const* list, int index);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Implementation  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -----  memory management  ----------------------------------------------- */

typedef struct {
    *(ELT) data;
    int len;
    int cap;
} LTN;

inline
LTN LTN##_init(int cap)
{
    return {
        malloc(sizeof(ELT)*cap),
        0,
        cap
    };
}

inline
void LTN##_free(LTN* list)
{
    free(list->data);
    *list = {NULL, 0, 0};
}

void LTN##_resize(LTN* list, int cap)
{
    if ( ! (list->len < cap) ) { return; }
    *(ELT) data = malloc(sizeof(ELT)*cap);
    for (int i = 0; i != list->len; ++i) { data[i] = list->data[i]; }
    free(list->data);
    *list = {data, list->len, cap};
}

inline
int LTN##_len(LTN const* list)
{
    return list->len;
}

inline
bool LTN##_is_empty(LTN const* list)
{
    return list->len == 0;
}

inline
bool LTN##_is_full(LTN const* list)
{
    return list->len == list->cap;
}

/* -----  unsafe accessors (no expanding, no bounds checks)  --------------- */

inline
void LTN##_push_unsafe(LTN* list, (ELT) el)
{
    list->data[list->len] = el;
    ++list->len;
}

inline
*(ELT) LTN##_pop_unsafe(LTN* list)
{
    return &(list->data[ --(list->len) ]);
}

inline
*(ELT) LTN##_top_unsafe(LTN void* list)
{
    return &(list->data[list->len]);
}

inline
*(ELT) LTN##_getref_unsafe(LTN const* list, int index)
{
    return &(list->data[index]);
}

/* -----  safe accessors (expand or return NULL as needed)  ---------------- */

void LTN##_push(LTN* list, (ELT) el)
{
    if ( LTN##is_full(list) ) { LTN##_resize(list, 1 + MUL_FACTOR*cap); }
    LTN##_push_unsafe(list, el);
}

inline
*(ELT) LTN##_pop(LTN* list)
{
    if ( LTN##is_empty(list) ) { return NULL; }
    return LTN##_pop_unsafe(list);
}

inline
*(ELT) LTN##_top(LTN const* list)
{
    if ( LTN##is_empty(list) ) { return NULL; }
    return LTN##_top_unsafe(list);
}

inline
*(ELT) LTN##_getref(LTN const* list, int index)
{
    if ( ! ( 0<=index && index<list->len) ) { return NULL; }
    return LTN##_top(list);
}



/* ========================================================================= */



#undef ELT ELEMENT_TYPE
#undef LMP LIST_METHOD_PREFIX
#undef LTN LIST_TYPE_NAME

