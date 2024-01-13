#ifndef PP_TRICKS
#define PP_TRICKS

#ifndef TRIVIAL_FUNC_DEFN
void TRIVIAL_FUNC() {}
#define EXPECT_PARENS TRIVIAL_FUNC
#endif//TRIVIAL_FUNC_DEFN

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  PP Variable Magic  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// to print value of a PreProc variable (named FOO_BAR, say):
//
//      #pragma message(STRING( FOO_BAR ))
//
#define STRING_INNER(x) #x
#define STRING(x) STRING_INNER(x)

// to define a concatenation of *expansions of two* names (say, FOO and BAR):
//
//      #define MY_BIG_NAME   CONCAT(FOO, BAR)
//
#define CONCAT_INNER(X,Y) X ## Y
#define CONCAT(X,Y) CONCAT_INNER(X,Y)

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Control Flow Idiom Shorthands  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define FOR(VAR, START, END) for (int VAR=START; VAR!=END; ++VAR)

#define BREAKBLOCK switch (0) default:

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Types  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#define CAST_AS(T, X)   ((T)X)
//  #define CAST_AS(T, X)   \
//      (*(                 \
//         (T *)(&(X))     \
//      ))

/* ========================================================================= */
/* =  IO / External Helpers  =============================================== */
/* ========================================================================= */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Color Printing  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define BLACK       printf("\033[30m"); EXPECT_PARENS
#define RED         printf("\033[31m"); EXPECT_PARENS
#define GREEN       printf("\033[32m"); EXPECT_PARENS
#define YELLOW      printf("\033[33m"); EXPECT_PARENS
#define BLUE        printf("\033[34m"); EXPECT_PARENS
#define PURPLE      printf("\033[35m"); EXPECT_PARENS
#define CYAN        printf("\033[36m"); EXPECT_PARENS
#define WHITE       printf("\033[37m"); EXPECT_PARENS

#define DEFAULT_COLOR       CYAN

#define _W_ ,

#define BARK_INNER(BODY, C)   { C(); BODY;               DEFAULT_COLOR(); } EXPECT_PARENS

#define BARK(MESSAGE, C)    BARK_INNER( { printf(MESSAGE);               } , C)
#define BARKLN(MESSAGE, C)  BARK_INNER( { printf(MESSAGE); printf("\n"); } , C)

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  Timeing Helpers  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <time.h>

#define START_CLOCK()           \
    clock_t _start, _diff;      \
    int _msec;                  \
    RESET_CLOCK();              \

#define RESET_CLOCK()           \
    _start = clock();

#define REPORT_CLOCK(Msg)                                                   \
    _diff = clock() - _start;                                               \
    _msec = _diff * 1000 / CLOCKS_PER_SEC;                                  \
    printf("%s \t took %d.%03d seconds\n", Msg, _msec/1000, _msec%1000);

#endif//PP_TRICKS
