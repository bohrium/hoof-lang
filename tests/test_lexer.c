#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "../preprocessor_tricks.h"

#include "../cstring.h"
#include "../list.h"
#include "../rawstring.h"
#include "../string.h"

#include "../lexer.h"

void test_good_path_pipeline();
void test_indents();
void test_symbols();
void test_identifier_names_a();
void test_identifier_names_b();

void print_word_wrapped(StringList const* tokens, int col_wrap)
// can go beyond `col_wrap` if token too long
{
    int col=0;
    for (int i=0; i!=tokens->len; ++i) {
        CString ss = tokens->data[i].raw.data;
        int del = cstr_len(ss);
        col += cstr_len("[  ]")+del;
        if ( col >= col_wrap ) { printf("\n"); col = cstr_len("[  ]")+del; }
        BARK("[ ", WHITE);
        BARK("%s" _W_ ss, PURPLE);
        BARK(" ]", WHITE);
    }
    printf("\n");
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

    DEFAULT_COLOR();
    BARKLN("hi!", CYAN);

    BARKLN("\n# Okay Lexing", BLUE);
    test_good_path_pipeline();

    BARKLN("\n# Indents", BLUE);
    test_indents();

    BARKLN("\n# Symbols", BLUE);
    test_symbols();

    BARKLN("\n# Bad Identifier Names", BLUE);
    test_identifier_names_a();
    test_identifier_names_b();



    BARKLN("bye!", CYAN);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~  _  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

//int VERBOSE_REPORT;
void report_on(char const* program_text)
{
    String s = str_init_as(program_text);
    YELLOW; str_println(&s);

    StringList lines;
    StringList tokens;
    {
        //BARKLN("[A]", BLUE);
        lines = lines_of(s.raw.data);
        //BARKLN("[B]", BLUE);
        tokens = tokenize(&lines);
        //BARKLN("[C]", BLUE);
        print_word_wrapped(&tokens, 80);
        //BARKLN("[D]", BLUE);
    }
    while (strl_len(&tokens)) { str_free(strl_pop(&tokens)); }
    strl_free(&tokens);
    while (strl_len(&lines)) { str_free(strl_pop(&lines)); }
    strl_free(&lines);

    str_free(&s);
}

void test_good_path_pipeline()
{
    report_on(
      "-- this is a comment, then a blank line                      \n"
      "my_identifier:MyTypeName                                     \n"
      "indentation_test                                             \n"
      "  ! body ( func arg arg ) . superfunc                        \n"
      );
}

void test_indents()
{
    report_on(
      "                     \n"
      "moo0                 \n"
      "  goo1 goo1          \n"
      "    gai2 gai2 gai2   \n"
      "  goo1               \n"
      "  goo-start          \n"
      "                     \n"
      "\n"
      "  goo-end            \n"
      "  --various gaps\n"
      "    gai2             \n"
      "      pan3           \n"
      "                     \n"
      "end                  \n"
      "                     \n"
      );
}

void test_symbols()
{
    report_on(
      " *{![[<<a=b>>]]};;: \n"
    );
}

void test_identifier_names_a()
{
    report_on(
      " -google-fruit --bad                                         \n"
      " _google_fruit --bad                                         \n"
      " google-fruit  --okay                                        \n"
      " google-fruit- --bad                                         \n"
      " google_fruit  --okay                                        \n"
      " google_fruit_ --bad                                         \n"
      " googleFruit   --okay                                        \n"
      " googleFruit69 --okay                                        \n"
      " 69googleFruit --bad                                         \n"
    );
}

void test_identifier_names_b()
{
    report_on(
      //" C           --bad       \n"
      //" CSTRING     --bad       \n"
      " CStr_ing    --okay      \n"
      " CString     --okay      \n"
      " CString_    --bad       \n"
      //" MooM        --bad       \n"
      " MooMitten   --okay      \n"
      " _CString    --bad       \n"
    );
}

