# brainfuck
A Brainfuck interpreter written in C++

## the language
The Brainfuck machine data consists of an array of bytes and a pointer initially pointing to the leftmost byte of the array.
The language uses only eight one-character instructions listed below.

\> :    increment the pointer

\< :    decrement the pointer

\+ :    increment the value under the pointer

\- :    decrement the value under the pointer

\. :    write the value under the pointer to standard output using ASCII format

\, :    read from standard input to the value under the pointer

\[ :    if the value under the pointer is null, jump to the corresponding closing bracket

\] :    if the value under the pointer is not null, jump to the corresponding opening bracket
