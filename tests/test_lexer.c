#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "../preprocessor_tricks.h"

#include "../cstring.h"
#include "../list.h"
#include "../rawstring.h"
#include "../string.h"

#include "../lexer.h"

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

    DEFAULT_COLOR();
    BARKLN("hi!", CYAN);

    String s = str_init_as(
      "-- this is a comment, then a blank line                      \n"
      "                                                             \n"
      "my_identifier:MyTypeName                                     \n"
      "                                                             \n"
      "indentation_test                                             \n"
      "  inside_block_the_first                                     \n"
      "    super_inner                                              \n"
      "  more_body                                                  \n"
      "  ! body ( func arg arg ) . superfunc                        \n"
      "  inside_block_the_second                                    \n"
      "    super_inner                                              \n"
      "                                                             \n"
      "outside_block                                                \n"
    );
    YELLOW; str_println(&s);

    StringList lines;
    StringList tokens;
    {
        BARKLN("[A]", BLUE);
        lines = lines_of(s.raw.data);
        BARKLN("[B]", BLUE);
        tokens = tokenize(&lines);
        BARKLN("[C]", BLUE);

        int col=0;
        for (int i=0; i!=tokens.len; ++i) {
            CString ss = tokens.data[i].raw.data;
            int del = cstr_len(ss);
            col += cstr_len("[  ]")+del;
            if ( col >= 80 ) { printf("\n"); col = del; }
            BARK("[ ", WHITE);
            BARK("%s" _W_ ss, PURPLE);
            BARK(" ]", WHITE);
        }
        printf("\n");
        BARKLN("[D]", BLUE);
    }
    while (strl_len(&tokens)) { str_free(strl_pop(&tokens)); }
    strl_free(&tokens);
    while (strl_len(&lines)) { str_free(strl_pop(&lines)); }
    strl_free(&lines);

    str_free(&s);
    BARKLN("bye!", CYAN);
}
