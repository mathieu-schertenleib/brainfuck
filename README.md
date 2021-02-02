# brainfuck

A Brainfuck interpreter written in C++

## The machine

The memory consists of an array of 30,000 bytes, initially set to zero. A single pointer is the unique way to interract
with it. It is initialised pointing to the leftmost byte of the array.

## The language

The language uses only eight one-character instructions listed below.

`>` move the pointer right

`<` move the pointer left

`+` increment the value at the pointer

`-` decrement the value at the pointer

`.` write the value at the pointer to standard output using ASCII format

`,` read from standard input to the value at the pointer

`[` if the value at the pointer is null, jump to the corresponding closing bracket

`]` if the value at the pointer is not null, jump to the corresponding opening bracket

Any other character is considered a comment and ignored.
