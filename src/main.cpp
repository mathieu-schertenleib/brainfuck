#include "brainfuck.hpp"

#include <iostream>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 2)
    {
        try
        {
            bf::Interpreter interpreter;
            interpreter.execute(bf::tokenise(bf::file_to_string(argv[1])));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what();
            return EXIT_FAILURE;
        }
    }
    else
    {
        std::cout << "Brainfuck interpreter\n"
                     "\n"
                     "Usage :\n"
                     "\tbrainfuck <filename>\n";
    }

    return EXIT_SUCCESS;
}
