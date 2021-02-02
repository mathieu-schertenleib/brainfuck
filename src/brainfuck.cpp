#include "brainfuck.hpp"

#include <iostream>

namespace bf
{
[[nodiscard]] auto file_to_string(const std::string &filename) -> std::string
{
    std::ifstream is(filename, std::ios::ate);

    if (!is.is_open())
    {
        throw std::runtime_error("Failed to open file \"" + filename + "\"\n");
    }

    std::string str;
    str.reserve(is.tellg());
    is.seekg(0);

    str.assign((std::istreambuf_iterator<char>(is)),
               std::istreambuf_iterator<char>());

    return str;
}

[[nodiscard]] auto tokenise(const std::string &program) -> std::vector<Token>
{
    std::vector<Token> tokens;
    for (const auto character : program)
    {
        switch (character)
        {
        case '+':
            tokens.push_back(Token::increment_value);
            break;
        case '-':
            tokens.push_back(Token::decrement_value);
            break;
        case '>':
            tokens.push_back(Token::increment_pointer);
            break;
        case '<':
            tokens.push_back(Token::decrement_pointer);
            break;
        case '.':
            tokens.push_back(Token::output_value);
            break;
        case ',':
            tokens.push_back(Token::input_value);
            break;
        case '[':
            tokens.push_back(Token::begin_loop);
            break;
        case ']':
            tokens.push_back(Token::end_loop);
            break;
        default:
            break;
        }
    }

    return tokens;
}

void Interpreter::execute(const std::vector<Token> &tokens)
{
    const auto program_end {tokens.end()};

    for (auto instruction_pointer {tokens.begin()};
         instruction_pointer != program_end; ++instruction_pointer)
    {
        switch (*instruction_pointer)
        {
        case Token::increment_value:
            increment_value();
            break;
        case Token::decrement_value:
            decrement_value();
            break;
        case Token::increment_pointer:
            increment_pointer();
            break;
        case Token::decrement_pointer:
            decrement_pointer();
            break;
        case Token::output_value:
            output_value();
            break;
        case Token::input_value:
            input_value();
            break;
        case Token::begin_loop:
            start_loop(instruction_pointer);
            break;
        case Token::end_loop:
            end_loop(instruction_pointer);
            break;
        default:
            return;
        }
    }
}

void Interpreter::increment_pointer() noexcept
{
    ++m_ptr;
}

void Interpreter::decrement_pointer() noexcept
{
    --m_ptr;
}

void Interpreter::increment_value() noexcept
{
    ++*m_ptr;
}

void Interpreter::decrement_value() noexcept
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

void Interpreter::start_loop(std::vector<Token>::const_iterator &it) const
{
    if (*m_ptr == 0)
    {
        unsigned int loop_counter {1};
        while (loop_counter > 0)
        {
            ++it;
            if (*it == Token::end_loop)
            {
                --loop_counter;
            }
            else if (*it == Token::begin_loop)
            {
                ++loop_counter;
            }
        }
    }
}

void Interpreter::end_loop(std::vector<Token>::const_iterator &it) const
{
    if (*m_ptr != 0)
    {
        unsigned int loop_counter {1};
        while (loop_counter > 0)
        {
            --it;
            if (*it == Token::begin_loop)
            {
                --loop_counter;
            }
            else if (*it == Token::end_loop)
            {
                ++loop_counter;
            }
        }
    }
}
} // namespace bf