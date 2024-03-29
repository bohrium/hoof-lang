#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "list.h"
#include "cstring.h"
#include "string.h"
#include "rawstring.h"
#include "lexer.h"

#include "preprocessor_tricks.h"

char const*   INDENT = "{-INDENT-}";
char const* UNINDENT = "{-DEDENT-}";
char const* NEWLINE  = "{-NEWLINE-}";

int get_indent(String const* line)
{
    int i;
    for (i = 0; i != str_len(line); ++i) {
        if ( str_at(line, i) != ' ' ) { break; }
    }
    return i;
}

bool is_digit(char c) { return ('0'<=c && c<='9'); }
bool is_upper(char c) { return ('A'<=c && c<='Z'); }
bool is_lower(char c) { return ('a'<=c && c<='z'); }
bool is_score(char c) { return (          c=='_'); }
bool is_hyphe(char c) { return (          c=='-'); }
bool is_space(char c) { return (          c==' '); }

bool is_alpha(char c) { return is_upper(c) || is_lower(c); }
bool is_horiz(char c) { return is_score(c) || is_hyphe(c); }

int try_match_space(CString cp)
{
    CString it = cp;
    if ( ! is_space(*it) ) { ++it; }
    // return token length
    return it-cp;
}

int try_match_word(CString cp)
{
    CString it = cp;

    // must start with alpha (else reject)
    if ( ! is_alpha(*it) ) { return 0; }

    // body may consist of alpha, digit, underscore, or hyphen
    while ( is_alpha(*it) || is_digit(*it) || is_horiz(*it) ) { ++it; }

    //  // must end with alpha or digit (else reject)
    if ( ! ( is_alpha(*(it-1)) || is_digit(*(it-1)) ) ) { return 0; }

    // return token length
    return it-cp;
}

int try_match_punct(CString cp)
{
#define __MATCH(STR) \
    if ( cstr_match_substring(cp, STR) ) { return cstr_len(STR); }
#define __MATCHPAIR(OPEN, CLOSE) \
    { __MATCH(OPEN); __MATCH(CLOSE); }

    __MATCH("=");
    __MATCH("\\");
    __MATCH(".");
    __MATCH("(");           __MATCH(")");

    __MATCH("*");
    __MATCH("!");
    __MATCH(";");
    __MATCH("{");           __MATCH("}");

    __MATCH(":");
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

int LINE_NUMBER;

int add_token(StringList* token_list, String const* line, int index)
// assumes lines null terminated
{
    // chomp leading whitespace; early return if no more tokens
    while ( str_match_at(line, index, " ") ) { ++index; }
    char last = str_at(line, index);
    if ( last=='\0' || last=='\n' )        { return -1; }

    /* ATTN : `words` include keywords, term identifiers, type identifiers */

    int toklen;
    BREAKBLOCK {
        if ( toklen=try_match_word   (line->raw.data + index) ) { break; }
        if ( toklen=try_match_punct  (line->raw.data + index) ) { break; }
    }
    if ( ! toklen ) {
        if ( try_match_comment(line->raw.data + index) ) {
            //BARKLN("comment", CYAN);
        }
        else {
            /* TODO: complain!  getting here means a parse error */
            BARKLN(" at line %d : unable to match : " _W_ LINE_NUMBER, RED);
            BARK("    ", WHITE);
            BARK("[", WHITE);
            BARK("%s" _W_ line->raw.data + index, BLUE);
            BARK("]\n", WHITE);
        }
        return -1;
    }

    String s = str_init(0);
    for (int i=0; i!=toklen; ++i) { str_push(&s, str_at(line, index+i)); }
    //str_null_terminate(&s);
    strl_push(token_list, s);
    return index+toklen;
}

TokenList tokenize(StringList const* lines)
// assumes lines null terminated
{
    TokenList tl = strl_init(0);

    IntList indent_stack = il_init(0);
    il_push(&indent_stack, 0);

    FOR (n, 0, strl_len(lines)) {
        LINE_NUMBER = n;

        String const* ln = strl_getref(lines, n);
        //BARKLN("line %d (%s)" _W_ n _W_ ln->raw.data, BLUE);

        int indent = get_indent(ln);
        //BARKLN("indentation is %d" _W_ indent, CYAN);
        if ( indent == str_len(ln) ) {
            //BARKLN("BLANK LINE", CYAN);
            continue;
        }

        // TODO : check here for uninteresting (just empty/whitespace/comment) line; if so, don't emit

        switch ( COMPARE(indent, *il_top(&indent_stack)) ) {
          break; case GT:
            il_push(&indent_stack, indent);
            strl_push(&tl, str_init_as(INDENT));
            //BARKLN("INDENT to %d\n" _W_ indent, CYAN);
          break; case EQ:
            strl_push(&tl, str_init_as(NEWLINE));
          break; case LT:
            while ( indent < *il_top(&indent_stack) ) {
                il_pop(&indent_stack);
                //BARKLN("DEDENT to %d\n" _W_ indent, CYAN);
                strl_push(&tl, str_init_as(UNINDENT));
            }
        }

        int d = indent;
        while ( str_at(ln, d) ) {
            int tt = add_token(&tl, ln, d);
            if ( tt==-1 ) { break; }
            d = tt;
        }
    }

    int indent = 0;
    while ( indent < *il_top(&indent_stack) ) {
        il_pop(&indent_stack);
        //BARKLN("DEDENT to %d\n" _W_ indent, CYAN);
        strl_push(&tl, str_init_as(UNINDENT));
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
            //str_null_terminate(&s); /*important!*/
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
