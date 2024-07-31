what is a parser?

- reads some text and produces a data structure (AST in this case)

we're gonna implement a top-down recursive descent parser, also known as a Pratt parser
- Start from the root of the tree and work our way down to the leaves

we need a parser such that it produces an AST that can portray the original source code
understanding monkey lang

`let <identifier> = <expression>`
currently at page 35
