#include "brainfuck.hpp"

#include <iostream>

Bf_interpreter::Bf_interpreter(std::size_t memory_size)
    : m_memory(memory_size), m_ptr{m_memory.begin()}
{
}

void Bf_interpreter::execute(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: failed to open file \"" << filename << "\"\n";
        exit(EXIT_FAILURE);
    }

    char c{};
    while (file.get(c))
    {
        switch (c)
        {
        case '<': decrement_ptr(); break;
        case '>': increment_ptr(); break;
        case '+': increment_value(); break;
        case '-': decrement_value(); break;
        case '.': output_value(); break;
        case ',': input_value(); break;
        case '[': start_loop(file); break;
        case ']': end_loop(file); break;
        default: break;
        }
    }

    file.close();
}

void Bf_interpreter::decrement_ptr()
{
    if (m_ptr > m_memory.begin())
    {
        --m_ptr;
    }
    else
    {
        std::cerr << "Error: out of bound index: -1\n";
        exit(EXIT_FAILURE);
    }
}

void Bf_interpreter::increment_ptr()
{
    if (m_ptr < m_memory.end() - 1)
    {
        ++m_ptr;
    }
    else
    {
        std::cerr << "Error: out of bound index: " << m_memory.size() << '\n';
        exit(EXIT_FAILURE);
    }
}

void Bf_interpreter::increment_value()
{
    if (*m_ptr < 255)
    {
        ++*m_ptr;
    }
    else
    {
        std::cerr << "Error: overflow at index " << m_ptr - m_memory.begin()
                  << '\n';
        exit(EXIT_FAILURE);
    }
}

void Bf_interpreter::decrement_value()
{
    if (*m_ptr > 0)
    {
        --*m_ptr;
    }
    else
    {
        std::cerr << "Error: underflow at index " << m_ptr - m_memory.begin()
                  << '\n';
        exit(EXIT_FAILURE);
    }
}

void Bf_interpreter::output_value() const
{
    std::cout << *m_ptr;
}

void Bf_interpreter::input_value()
{
    *m_ptr = 0;
    std::cin >> *m_ptr;
}

void Bf_interpreter::start_loop(std::ifstream &file) const
{
    if (*m_ptr == 0)
    {
        unsigned int bracket_counter{1};
        char c{};
        while (bracket_counter > 0)
        {
            file.get(c);
            if (c == '[')
                ++bracket_counter;
            else if (c == ']')
                --bracket_counter;
        }
    }
}

void Bf_interpreter::end_loop(std::ifstream &file) const
{
    if (*m_ptr > 0)
    {
        unsigned int bracket_counter{1};
        char c{};
        while (bracket_counter > 0)
        {
            file.unget();
            file.unget();
            file.get(c);

            if (c == ']')
                ++bracket_counter;
            else if (c == '[')
                --bracket_counter;
        }
    }
}
