# Formal Logic Calculator 
At this point, this is intended to be a sentential logic calculator that takes no variables, has no symbol table, pretty printing, or extended features. 

### Intended Features in the Short Term:
- [ ] Provisional specification for the syntax, lexical elements, formal grammar and language that this simple calculator will support.
- [ ] Lexer, Parser, and routines for semantic analysis, all according to the aforementioned language specification.
- [ ] A set of subroutines that evaluate the result of binary operations on truth values.
- [ ] A wrapper/driver around these technologies that create a pipline for that information in such a way that a client can send expressions to 
its standard input and it will print the result to standard output.
- [ ] Configuration options to control the error reporting (or lack thereof) in a parse-reliable way so as to make it possible to integrate the driver
with other software.
