#include "istream_wrapper.h"

IStreamWrapper::IStreamWrapper(std::istream& str) : str_(str), buf_(0), id_bit_(8) {}

uint16_t IStreamWrapper::Get8b() const {                   // returns read char or END_OF_FILE
    char c;
    str_.read(&c, 1);
    if (!str_.gcount()) {                                  // check for end of file
        return END_OF_FILE;
    }
    return static_cast<uint8_t>(c);                        // it's essential that c overflowing like uint8_t,
                                                           // not like uint16_t
}

bool IStreamWrapper::ResetBuf() {
    buf_ = Get8b();
    id_bit_ = 0;
    return (buf_ != END_OF_FILE);
}

uint16_t IStreamWrapper::GetBits(size_t n) {
    uint16_t res = 0;
    for (size_t cnt_read = 0; cnt_read < n; cnt_read++) {
        uint16_t bit = Get1b();
        if (bit == END_OF_FILE) {
            return END_OF_FILE;
        }
        if (bit) {
            res |= (1 << cnt_read);
        }
    }
    return res;
}

uint16_t IStreamWrapper::Get1b() {
    if (id_bit_ == 8) {
        if (!ResetBuf()) {
            return END_OF_FILE;
        }
    }
    uint16_t bit = ((buf_ & (1 << id_bit_)) >> id_bit_);
    id_bit_++;
    return bit;
}
