#include "brainfuck.hpp"

#include <iostream>

namespace brainfuck
{
Program::Program(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }

    char c {};
    while (file.get(c))
    {
        switch (c)
        {
        case '+':
            instructions.push_back(Instruction::increment_value);
            break;
        case '-':
            instructions.push_back(Instruction::decrement_value);
            break;
        case '>':
            instructions.push_back(Instruction::increment_pointer);
            break;
        case '<':
            instructions.push_back(Instruction::decrement_pointer);
            break;
        case '.':
            instructions.push_back(Instruction::output_value);
            break;
        case ',':
            instructions.push_back(Instruction::input_value);
            break;
        case '[':
            instructions.push_back(Instruction::loop_start);
            break;
        case ']':
            instructions.push_back(Instruction::loop_end);
            break;
        default:
            break;
        }
    }

    file.close();
}

void Interpreter::execute(const Program &program)
{
    Program::Iterator instruction_pointer {program.instructions.cbegin()};
    Program::Iterator program_end {program.instructions.cend()};

    for (; instruction_pointer != program_end; ++instruction_pointer)
    {
        switch (*instruction_pointer)
        {
        case Instruction::increment_value:
            increment_value();
            break;
        case Instruction::decrement_value:
            decrement_value();
            break;
        case Instruction::increment_pointer:
            increment_pointer();
            break;
        case Instruction::decrement_pointer:
            decrement_pointer();
            break;
        case Instruction::output_value:
            output_value();
            break;
        case Instruction::input_value:
            input_value();
            break;
        case Instruction::loop_start:
            start_loop(instruction_pointer);
            break;
        case Instruction::loop_end:
            end_loop(instruction_pointer);
            break;
        default:
            return;
        }
    }
}

void Interpreter::increment_pointer()
{
    if (m_ptr < m_memory.end() - 1)
    {
        ++m_ptr;
    }
    else
    {
        throw std::runtime_error("Out of bound pointer");
    }
}

void Interpreter::decrement_pointer()
{
    if (m_ptr > m_memory.begin())
    {
        --m_ptr;
    }
    else
    {
        throw std::runtime_error("Out of bound pointer");
    }
}

void Interpreter::increment_value()
{
    ++*m_ptr;
}

void Interpreter::decrement_value()
{
    --*m_ptr;
}

void Interpreter::output_value() const
{
    std::cout << *m_ptr;
}

void Interpreter::input_value()
{
    std::cin >> *m_ptr;
}

void Interpreter::start_loop(Program::Iterator &it) const
{
    if (*m_ptr == 0)
    {
        unsigned int loop_counter {1};
        while (loop_counter > 0)
        {
            ++it;
            if (*it == Instruction::loop_start)
                ++loop_counter;
            else if (*it == Instruction::loop_end)
                --loop_counter;
        }
    }
}

void Interpreter::end_loop(Program::Iterator &it) const
{
    if (*m_ptr > 0)
    {
        unsigned int loop_counter {1};
        while (loop_counter > 0)
        {
            --it;
            if (*it == Instruction::loop_end)
                ++loop_counter;
            else if (*it == Instruction::loop_start)
                --loop_counter;
        }
    }
}
} // namespace brainfuck