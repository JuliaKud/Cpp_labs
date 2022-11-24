Implementation of an assembler-like programming language interpreter.
Exactly ten registers are available in this language, with names from `$0` to `$9`,
each register stores an arbitrary-sized matrix of integer elements.
Commands: loading a matrix from a file into a register, displaying a register on the screen,
addition, multiplication of registers and output of a matrix element.
Each register by default stores a matrix of size `0x0`.
Exceptions are used to handle errors.

#### `load`
It takes exactly two parameters: case and filename.
Loads a matrix from a file into a register.

### `print`
It takes one parameter: register.
Line by line prints the elements of a matrix stored in `<reg>`.

### `elem`
It takes three parameters: case, row and column number (numbering from zero).
Prints the corresponding element of the matrix to the screen.

### `exit`
Successfully exits the interpreter.

### `add`
It takes two parameters: registers `A` and `B`.
Writes to `A` the result of `A + B`.

### `mul`
It takes two parameters: registers `A` and `B`.
Writes to `A` the result of `A * B`.