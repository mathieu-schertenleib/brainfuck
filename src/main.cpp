#include "brainfuck.hpp"

#include <iostream>

namespace
{
constexpr auto usage = R"(Brainfuck interpreter

Usage:
    brainfuck <filename> [--memory=<B>]
    brainfuck [-h | --help]

Options:
    -h --help       Show this screen
    --memory=<B>    Set the amount of bytes allocated [default: 30000]
)";
} // namespace

auto main(int argc, char *argv[]) -> int
{
    Bf_interpreter bfi;

    // TODO: parse command line parameters

    if (argc == 2)
    {
        bfi.execute(argv[1]);
    }
    else
    {
        std::cerr << usage;
    }

    return 0;
}
