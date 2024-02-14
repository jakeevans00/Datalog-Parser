# Build an Interpreter for the Datalog Language

### Scanner (Lexer)
Create a lexer that tokenizes input. Input files are read and split based on grammar rules for the Datalog language.
Terminals are specified in the `enum TokenType` in the `Token.h` file. Tokens are added to a vector which can be handed
off to the parser object.

### Parser
Takes a vector of tokens as input and performs 2 high-level functions. 
First, it checks for syntax correctness using a 
recursive descent parser (for an LL(1) grammar). If syntax is incorrect, errors will be thrown indicating the tokenType, 
tokenValue, and lineNumber that caused the error. 
Second, it creates a Datalog object based to be used by future components. 
