#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "../cstring.h"
#include "../rawstring.h"
#include "../string.h"

#define CHECK_MATCH(S,I,P,A)                        \
    {                                               \
        int  mm = str_match_at(&S, I, P) ? 1 : 0;   \
        printf("%s (answered %s)\n",                \
                (mm==A ? "pass" : "FAIL"),          \
                (mm ? "yes" : "no"));               \
    }

int main(int argc, char const* const* argv)
{
    if ( argc>=2 ) {
        BREAKBLOCK {
            if ( argc!=2 ) { BARKLN("expected 1 arg", RED); return -1; }
            if ( cstr_eq(argv[1], "color"   ) ) { USECOLOR = 1; break; }
            if ( cstr_eq(argv[1], "no-color") ) { USECOLOR = 0; break; }
            BARKLN("arg must be `color` or `no-color`", RED); return -1;
        }
    }

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
    str_append(&s, t.raw.data);
    printf("s: ");   str_println(&s);
    printf("t: ");   str_println(&t);
    str_copy_from(&t, s.raw.data);
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

