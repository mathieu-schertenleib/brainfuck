#include "brainfuck.hpp"

#include <iostream>

auto main(int argc, char *argv[]) -> int
{
    brainfuck::Interpreter interpreter;

    if (argc == 2)
    {
        try
        {
            brainfuck::Program program(argv[1]);
            interpreter.execute(program);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what();
        }
    }
    else
    {
        std::cerr << "Brainfuck interpreter\n"
                     "\n"
                     "Usage :\n"
                     "\tbrainfuck <filename>\n";
    }

    return 0;
}
