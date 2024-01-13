#include "stdbool.h"
#include "stdlib.h"
#include "preprocessor_tricks.h"

#define ELT ELEMENT_TYPE
#define LMP LIST_METHOD_PREFIX
#define LTN LIST_TYPE_NAME


//#pragma message(STRING( LIST_TYPE_NAME ))

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
/* ~  Interface  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* -----  pre-requisites  -------------------------------------------------- */

// ATTN the following macros must already be defined
#if    ! defined (ELEMENT_TYPE      ) /* type  */  \
    || ! defined (LIST_TYPE_NAME    ) /* ident */  \
    || ! defined (LIST_METHOD_PREFIX) /* ident */  \
    || ! defined (EXPAND_FACTOR     ) /* float */
  #error
#endif

/* -----  type and method declarations  ------------------------------------ */

typedef struct LTN {
    ELT* data;
    int len;
    int cap;
} LTN;

// memory management:
LTN     _INIT       (int cap);
void    _FREE       (LTN* list);
void    _RESIZE     (LTN* list, int cap);
int     _LEN        (LTN const* list);
bool    _IS_EMPTY   (LTN const* list);
bool    _IS_FULL    (LTN const* list);

// unsafe accessors (no expanding, no bounds checks):
void    _PUSH_UNSAFE    (LTN* list, ELT el);
ELT*    _POP_UNSAFE     (LTN* list);
ELT*    _TOP_UNSAFE     (LTN const* list);
ELT*    _GETREF_UNSAFE  (LTN const* list, int index);

// safe accessors (expand or return NULL as needed)
void    _PUSH   (LTN* list, ELT el);
ELT*    _POP    (LTN* list);
ELT*    _TOP    (LTN const* list);
ELT*    _GETREF (LTN const* list, int index);

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


