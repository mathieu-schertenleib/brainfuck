#ifndef BRAINFUCK_HPP
#define BRAINFUCK_HPP

#include <array>
#include <cstdint>
#include <fstream>
#include <vector>

namespace bf
{
enum struct Token : std::uint8_t
{
    increment_value,
    decrement_value,
    increment_pointer,
    decrement_pointer,
    output_value,
    input_value,
    begin_loop,
    end_loop
};

[[nodiscard]] auto file_to_string(const std::string &filename) -> std::string;
[[nodiscard]] auto tokenise(const std::string &program) -> std::vector<Token>;

class Interpreter
{
public:
    void execute(const std::vector<Token> &tokens);

private:
    std::array<std::uint8_t, 30000> m_memory {};
    std::uint8_t *m_ptr {m_memory.begin()};

    void increment_value() noexcept;
    void decrement_value() noexcept;
    void increment_pointer() noexcept;
    void decrement_pointer() noexcept;
    void output_value() const;
    void input_value();
    void start_loop(std::vector<Token>::const_iterator &it) const;
    void end_loop(std::vector<Token>::const_iterator &it) const;
};
} // namespace bf

#endif
