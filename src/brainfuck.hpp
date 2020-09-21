#ifndef BRAINFUCK_HPP
#define BRAINFUCK_HPP

#include <array>
#include <cstdint>
#include <fstream>
#include <vector>

namespace brainfuck
{
enum class Instruction : char
{
    increment_value,
    decrement_value,
    increment_pointer,
    decrement_pointer,
    output_value,
    input_value,
    loop_start,
    loop_end
};

struct Program
{
    explicit Program(const char *filename);

    std::vector<Instruction> instructions;

    using Iterator = decltype(instructions)::const_iterator;
};

class Interpreter
{
public:
    void execute(const Program &program);

private:
    std::array<unsigned char, 30000> m_memory {};
    decltype(m_memory)::iterator m_ptr {m_memory.begin()};

    void increment_value();
    void decrement_value();
    void increment_pointer();
    void decrement_pointer();
    void output_value() const;
    void input_value();
    void start_loop(Program::Iterator &it) const;
    void end_loop(Program::Iterator &it) const;
};
} // namespace brainfuck

#endif
