#ifndef BRAINFUCK_HPP
#define BRAINFUCK_HPP

#include <cstdint>
#include <fstream>
#include <vector>

class Bf_interpreter
{
public:
    explicit Bf_interpreter(std::size_t memory_size = 30000);

    void execute(const char *filename);

private:
    std::vector<std::uint8_t> m_memory;
    std::vector<std::uint8_t>::iterator m_ptr;

    void decrement_ptr();
    void increment_ptr();
    void increment_value();
    void decrement_value();
    void output_value() const;
    void input_value();
    void start_loop(std::ifstream &file) const;
    void end_loop(std::ifstream &file) const;
};

#endif
