" Vim syntax file
" Maintainer:       samtenka
" Latest Revision:  2023-11

if exists("b:current_syntax")
  finish
endif

"syn keyword moonotesSCTodo containedin=moonotesSCComment contained TODO FIXME XXX NOTE
"syn match   moonotesSCComment "#.*$" contains=moonotesSCTodo

"----------------------------------------------------------------------------/
"  Parsing Names
"----------------------------------------------------------------------------/

" SAM TENKA: color (uppercase identifier) as a type name
syntax match hoofType "^[A-Z][a-zA-Z0-9]\+"
syntax match hoofType "\([^-_a-zA-Z0-9]\)\@<=[A-Z][a-zA-Z0-9]\+"
hi hoofType ctermfg=Magenta

" SAM TENKA: color (lowercase identifier) as a term name
syntax match hoofTerm "^[a-z][a-zA-Z0-9]\+"
syntax match hoofTerm "\([^-_a-zA-Z0-9]\)\@<=[a-z][a-zA-Z0-9]\+"
hi hoofTerm ctermfg=White


" SAM TENKA: color symbols
syntax match hoofSymb "\\"
syntax match hoofSymb "="
syntax match hoofSymb "\."
syntax match hoofSymb ":"
syntax match hoofSymb "{"
syntax match hoofSymb "}"
syntax match hoofSymb "!"
syntax match hoofSymb "_"
hi hoofSymb ctermfg=Gray

" SAM TENKA: type system symbols
syntax match hoofTSymb "@"
syntax match hoofTSymb "->"
syntax match hoofTSymb "\*"
syntax match hoofTSymb "<<"
syntax match hoofTSymb ">>"
syntax match hoofTSymb "\[\["
syntax match hoofTSymb "\]\]"
hi hoofTSymb ctermfg=Brown

" SAM TENKA: type system symbols
syntax match hoofKW "is"
hi hoofKW ctermfg=DarkYellow cterm=bold


"----------------------------------------------------------------------------/
"  Parsing comments
"----------------------------------------------------------------------------/

" SAM TENKA: four kinds of moonotes comments:
"   todos (bg dark red),
"   docnotes/headings/labels to help skimming (fg brown),
"   commented code (fg dark gray), and
"   ordinary comments to discuss interfaces and annotate implementations (default = fg cyan)

" SAM TENKA: colorize haskell style comments
syn match cCodeComment "--.*$"
hi cCodeComment ctermfg=DarkGray

" SAM TENKA: colorize haskell-style comments beginning with a leftarrow or
" ending with colon
syn match cLabelComment "-- <- .*"
syn match cLabelComment "--[ ]\?.*:$"
hi cLabelComment ctermfg=Green

syn match cHeadingComment "--===.*==="
syn match cHeadingComment "--\~\~\~.*\~\~\~"
syn match cHeadingComment "---.*---"
hi cHeadingComment ctermfg=Cyan

"" SAM TENKA: highlight commented all-caps words followed by exlam or colon
"syn match cTodo contained "[A-Z]\+\ze\!"
"syn match cTodo contained "[A-Z]\+\ze:"
"highlight link cTodo Todo
"hi Todo ctermfg=DarkRed
""note: Todo bg/fg are flipped!

"----------------------------------------------------------------------------/
"  Setup syntax highlighting
"----------------------------------------------------------------------------/

"let b:current_syntax = "celstarcat"

"hi def link moonotesSCTodo          Todo
"hi def link moonotesSCComment       Comment
"hi def link moonotesSCStarBlockCmd  Statement
"hi def link moonotesSCMainKw        Keyword
"hi def link moonotesSCMainInnerKw   Special
"hi def link moonotesSCEllOrbitCmd   Statement
"hi def link moonotesSCHIPNumber     Type
"hi def link moonotesSCString        Constant
"hi def link moonotesSCDescString    PreProc
"hi def link moonotesSCNumber        Constant
"

