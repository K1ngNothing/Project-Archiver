#pragma once

#include <cstdint>
#include <iostream>

const size_t BUF_SIZE = 9;

class OStreamWrapper {
public:
    explicit OStreamWrapper(std::ostream& str);

    void Flush();
    void Put1b(uint8_t c);
    void Put9b(uint16_t c);

private:
    std::ostream& str_;
    char buf_[BUF_SIZE];
    uint8_t id_byte_;                            // number of filling byte in buf_
    uint8_t id_bit_;                             // number of first empty bit in cur byte
};