#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "../cstring.c"
#include "../string.c"

#define CHECK_MATCH(S,I,P,A)                        \
    {                                               \
        int  mm = str_match_at(&S, I, P) ? 1 : 0;   \
        printf("%s (answered %s)\n",                \
                (mm==A ? "pass" : "FAIL"),          \
                (mm ? "yes" : "no"));               \
    }

int main()
{
    printf("hi!\n");

    String s = str_init_as("woah ");
    String t = str_init_as("cow says moo ");

    CHECK_MATCH(s, 0, "woah "   , 1 );
    CHECK_MATCH(s, 0, "woah !"  , 0 );

    CHECK_MATCH(s,-1, ""        , 0 );
    CHECK_MATCH(s, 0, ""        , 1 );
    CHECK_MATCH(s, 5, ""        , 1 );
    CHECK_MATCH(s, 6, ""        , 0 );

    printf("s: ");   str_println(&s);
    printf("t: ");   str_println(&t);
    str_append(&s, t.data);
    printf("s: ");   str_println(&s);
    printf("t: ");   str_println(&t);
    str_copy_from(&t, s.data);
    printf("s: ");   str_println(&s);
    printf("t: ");   str_println(&t);

    CHECK_MATCH(s, 0, "wo"      , 1 );
    CHECK_MATCH(s, 0, "ww"      , 0 );
    CHECK_MATCH(s, 0, "oo"      , 0 );
    CHECK_MATCH(s, 1, "wo"      , 0 );
    CHECK_MATCH(s, 1, "oa"      , 1 );

    CHECK_MATCH(s, 5, "co"      , 1 );
    CHECK_MATCH(s, 9, "co"      , 0 );
    CHECK_MATCH(s, 9, "sa"      , 1 );

    str_free(&s);
    str_free(&t);

    printf("\nbye!\n");
    return 0;
}

