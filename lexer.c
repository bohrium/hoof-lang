#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "list.c"
#include "cstring.c"
#include "string.c"

typedef StringList TokenList;
typedef String Token;
char const*   INDENT = "{-INDENT-}\0";
char const* UNINDENT = "{-UNINDENT-}\0";
char const* COMMENT  = "{-COMMENT-}\0";

typedef enum {
    LT, EQ, GT
} COMPARE_T;
#define COMPARE(X,Y) ((X)<(Y) ? LT : (X)>(Y) ? GT : EQ)

int get_indent(String const* line)
{
    int i;
    for (i = 0; i != str_len(line); ++i) {
        if ( *line->data != ' ' ) { return i; }
    }
    return i;
}

bool is_digit(char c) { return ('0'<=c && c<='9'); }
bool is_upper(char c) { return ('A'<=c && c<='Z'); }
bool is_lower(char c) { return ('a'<=c && c<='z'); }
bool is_score(char c) { return (          c=='_'); }
bool is_hyphe(char c) { return (          c=='-'); }

bool is_alpha(char c) { return is_upper(c) || is_lower(c); }
bool is_horiz(char c) { return is_score(c) || is_hyphe(c); }

int try_match_word(CString cp)
{
    CString it = cp;

    // must start with alpha (else reject)
    if ( ! is_alpha(*it) ) { return 0; }

    // body may consist of alpha, digit, underscore, or hyphen
    while ( is_alpha(*it) || is_digit(*it) || is_horiz(*it) ) { ++it; }

    //  // must end with alpha or digit (else reject)
    //  if ( ! ( is_alpha(*(it-1)) || is_digit(*(it-1)) ) ) { return 0; }

    // return token length
    return it-cp;
}

int try_match_punct(CString cp)
{
#define __MATCH(STR) \
    if ( cstr_match_substring(cp, STR) ) { return cstr_len(STR); }
#define __MATCHPAIR(OPEN, CLOSE)  { __MATCH(OPEN); __MATCH(CLOSE); }

    __MATCH("=");
    __MATCH("\\");
    __MATCH(".");
    __MATCH("(");           __MATCH(")");

    __MATCH("*");
    __MATCH("!");
    __MATCH("{");           __MATCH("}");

    __MATCH("@");
    __MATCH("[[");          __MATCH("]]");
    __MATCH("<<");          __MATCH(">>");

    return 0;   /* no symbol recognized!  */
#undef __MATCHPAIR
#undef __MATCH
}

int try_match_comment(CString cp)
{
    if ( cstr_match_substring(cp, "--") ) { return cstr_len(cp); }
    return 0;   /* no symbol recognized!  */
}

int add_token(StringList* token_list, String const* line, int index)
// assumes lines null terminated
{
    while ( str_match_at(line, index, " ") )  { ++index; }
    if ( index == str_len(line) )             { return -1; }

    /* ATTN : `words` include keywords, term identifiers, type identifiers */

    int toklen;
    switch (0) { // ATTN : find nonzero toklen then IMMEDIATELY break
    default:    if ( toklen=try_match_word   (line->data + index) ) { break; }
                if ( toklen=try_match_punct  (line->data + index) ) { break; }
                if ( toklen=try_match_comment(line->data + index) ) { break; }
        /* TODO: complain!  getting here means a parse error or trailing whitespace! */
        printf(":-(\n");
    }

    if (toklen) {
        String s = str_init(0);
        for (int i=0; i!=toklen; ++i) { str_push(&s, line->data[index+i]); }
        str_null_terminate(&s);
        strl_push(token_list, s);
        return index+toklen;
    } else {
        return -1;
    }
}

TokenList tokenize(StringList const* lines)
// assumes lines null terminated
{
    TokenList tl = strl_init(0);

    IntList indent_stack = il_init(0);
    il_push(&indent_stack, 0);

    FOR (n, 0, strl_len(lines)) {
        String const* ln = strl_getref(lines, n);
        printf("line %d (%s)\n", n, ln->data);

        int indent = get_indent(ln);
        switch ( COMPARE(indent, *il_top(&indent_stack)) ) {
          break; case LT:
            il_push(&indent_stack, indent);
          break; case EQ:
          break; case GT:
            while ( indent < *il_top(&indent_stack) ) {
                il_pop(&indent_stack);
                strl_push(&tl, str_init_as(UNINDENT));
            }
        }

        int d = indent;
        while ( ln->data[d] ) {
            int tt = add_token(&tl, ln, d);
            if ( tt==-1 ) { break; }
            d = tt;
        }
    }

    il_free(&indent_stack);
    return tl;
}

StringList lines_of(CString text)
{
    StringList lines = strl_init(0);
    String s = str_init(0);

    // logic is made annoying because line might end in '\0' rather than '\n'
    // and we also want not to leak.
    while ( 1 ) {

        if ( *text=='\n' || *text=='\0' ) {
            str_null_terminate(&s); /*important!*/
            strl_push(&lines, s);
            s = str_init(0);
        } else {
            str_push(&s, *text);
        }

        if ( *text=='\0' ) { break; }

        ++text;
    }

    str_free(&s);

    return lines;
}


int main()
{
    printf("hi!\n");
    String s = str_init_as(
      "aoah!                                                       x\n"
      "boah!                                                        \n"
      "coah!         -- i am a comment                              \n"
      "xoah!                                                        \n"
      "yoah!                                                        \n"
      "zoah!                                                        "
    );
    str_print(&s);
    printf("\n");

    StringList lines;
    StringList tokens;
    {
        printf("[A]\n");
        lines = lines_of(s.data);
        for (int i=0; i!=lines.len; ++i) {
            printf("[[ %s ]]", lines.data[i].data);
        }

        printf("[B]\n");
        tokens = tokenize(&lines);
        printf("[C]\n");
        for (int i=0; i!=tokens.len; ++i) {
            printf("[[ %s ]]", tokens.data[i].data);
        }
        printf("[D]\n");
    }
    while (strl_len(&tokens)) { str_free(strl_pop(&tokens)); }
    strl_free(&tokens);
    while (strl_len(&lines)) { str_free(strl_pop(&lines)); }
    strl_free(&lines);

    str_free(&s);
    printf("bye!\n");
}
