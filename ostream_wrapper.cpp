#include "ostream_wrapper.h"
#include <iostream>

OStreamWrapper::OStreamWrapper(std::ostream& str) : str_(str), id_byte_(0), id_bit_(0) {
    for (size_t i = 0; i < BUF_SIZE; i++) {
        buf_[i] = 0;
    }
}

void OStreamWrapper::Flush() {
    if (id_bit_ == 0 && id_byte_ == 0) {                           // empty buf_
        return;
    }
    str_.write(buf_, id_byte_);                                    // granted filled
    if (id_bit_ != 0) {                                            // if the last byte isn't empty
        str_.write(&buf_[id_byte_], 1);
    }
    for (size_t i = 0; i < BUF_SIZE; i++) {                        // reset buf_
        buf_[i] = 0;
    }
    id_byte_ = 0;
    id_bit_ = 0;
}

void OStreamWrapper::Put1b(uint8_t c) {
    if (c == 1) {
        buf_[id_byte_] |= (1 << id_bit_);
    }
    id_bit_++;
    if (id_bit_ == 8) {
        id_bit_ = 0;
        id_byte_++;
        if (id_byte_ == BUF_SIZE) {                                // buf_ is full
            Flush();
        }
    }
}

void OStreamWrapper::Put9b(uint16_t c) {
    for (size_t j = 0; j < 9; j++) {
        Put1b((c & (1 << j)) >> j);
    }
}

