# hoof programming language specification

## syntax

### example

    main : *Unit
    main = {
        ! print "hello world"
    }

### lexing

We use haskell-esque indentation, which during lexing helps insert openers
`(=(` and closers `)=)`

    Identifiers : [a-z][_a-z]*
    Types       : [A-Z][A-Za-z0-9]+
    TypeVars    : _[a-z]

### grammar

    TYPE =
      | TYPENAME        -- includes basic types Char8, UInt32, etc
      | TYPE -> TYPE    -- function
      | [[ (TYPE)* ]]   -- product
      | << (TYPE)* >>   -- coproduct
      | * TYPE          -- impure
      | Ref TYPE        -- reference to
      | Ptr TYPE        -- pointer to
      | TYPE @ TYPE     -- poly specialization
      | TYPEVAR         -- poly
      | ( TYPE )        -- grouping

    -- pure expression
    EXPR =
      | IDEN            -- lambda
      | EXPR EXPR       -- application
      | \ IDEN EXPR     -- lambda
      | { CMND }        -- wrap a thunk ... x:T => {x}:*T
      | ( EXPR )        -- grouping
      | ref IDEN            -- address of a variable

    -- impure expression
    CMND =
      | EXPR                -- return val
      | ! EXPR              -- execute a thunk ... y:*T => !y:T with effects
      | EXPR << EXPR        -- assignment
      | CMND ; CMND         -- sequence
      | if (=( (GCMD)* )=)  -- dijkstra conditional
      | do (=( (GCMD)* )=)  -- dijkstra iteration
      | deref EXPR          -- dereference a reference or pointer
      | abort               -- generate exception

    GCMD =
      | EXPR ~> CMD
      | else ~> CMD

    DECL =
      | IDEN : TYPE             -- ordinary judgement
      | type TYPENAME = TYPE    -- define a type

    DEFN =
      | IDEN = EXPR             -- bind to pure expression



### hello
### hello
### hello
