#ifndef LEXER_H
#define LEXER_H

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "list.h"
#include "cstring.h"
#include "rawstring.h"
#include "string.h"

#include "preprocessor_tricks.h"

typedef StringList TokenList;
typedef String Token;
extern char const*   INDENT;
extern char const* UNINDENT;
extern char const* COMMENT ;

//  bool is_digit(char c) { return ('0'<=c && c<='9'); }
//  bool is_upper(char c) { return ('A'<=c && c<='Z'); }
//  bool is_lower(char c) { return ('a'<=c && c<='z'); }
//  bool is_score(char c) { return (          c=='_'); }
//  bool is_hyphe(char c) { return (          c=='-'); }
//  bool is_space(char c) { return (          c==' '); }
//  
//  bool is_alpha(char c) { return is_upper(c) || is_lower(c); }
//  bool is_horiz(char c) { return is_score(c) || is_hyphe(c); }

TokenList tokenize(StringList const* lines);
StringList lines_of(CString text);

#endif//LEXER_H
