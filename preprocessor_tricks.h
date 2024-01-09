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

#endif//PP_TRICKS