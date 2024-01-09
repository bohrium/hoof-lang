#ifndef PP_TRICKS
#define PP_TRICKS

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
