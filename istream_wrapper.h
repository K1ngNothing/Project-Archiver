#pragma once

#include <cstdint>
#include <istream>

#include "constants.h"

class IStreamWrapper {
public:
    explicit IStreamWrapper(std::istream& str);

    uint16_t GetBits(size_t n);

private:
    uint16_t Get8b() const;
    uint16_t Get1b();

    bool ResetBuf();

    std::istream& str_;
    uint16_t buf_;
    uint8_t id_bit_;                              // id of first not read bit; if id_bit_ == 8, then buffer is full
};