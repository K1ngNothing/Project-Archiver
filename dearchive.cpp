#include "dearchive.h"

void ReconstructCanonicHuffmanCodes(uint16_t symbol_count, const std::vector<uint16_t>& symbols,
                              std::unordered_map<uint16_t, std::string>& codes, IStreamWrapper& input_stream) {
    std::string cur_code;
    size_t id_of_coding_symbol = 0;
    for (size_t length = 1; symbol_count > 0; length++) {
        uint16_t length_count = input_stream.GetBits(9);
        if (length_count == END_OF_FILE || length_count > symbol_count) {
            throw std::invalid_argument("Incorrect archive format");
        }
        for (size_t dt = 0; dt < length_count; dt++) {
            uint16_t symbol = symbols[id_of_coding_symbol];
            MakeNextCanonicCode(cur_code, length);
            codes[symbol] = cur_code;
            id_of_coding_symbol++;
        }
        symbol_count -= length_count;
    }
}

uint16_t ReadOneSymbol(IStreamWrapper& input_stream, Trie& trie) {
    size_t cur_t = 0;
    uint16_t symbol;
    while (1) {                                                       // reading 1 symbol;
        uint16_t bit = input_stream.GetBits(1);
        if (bit == END_OF_FILE) {
            throw std::invalid_argument("Incorrect archive format");
        } else {
            cur_t = trie.GoTo(cur_t, bit);
            if (trie[cur_t].vertex.symbol != END_OF_FILE) {           // terminal vertex
                symbol = trie[cur_t].vertex.symbol;
                break;
            }
        }
    }
    return symbol;
}

std::pair<size_t, std::vector<uint16_t>> GetInfoForReconstructingCodes(IStreamWrapper& input_stream) {
    uint16_t symbol_count = input_stream.GetBits(9);
    if (symbol_count == END_OF_FILE) {
        throw std::invalid_argument("Incorrect archive format");
    }
    std::vector<uint16_t> symbols(symbol_count);
    for (size_t i = 0; i < symbol_count; i++) {
        symbols[i] = input_stream.GetBits(9);
        if (symbols[i] == END_OF_FILE) {
            throw std::invalid_argument("Incorrect archive format");
        }
    }
    return {symbol_count, symbols};
}

std::string DearchiveFileName(IStreamWrapper& input_stream, Trie& trie) {
    std::string file_name;
    while (1) {
        uint16_t symbol = ReadOneSymbol(input_stream, trie);
        if (symbol == FILENAME_END) {
            break;
        }
        file_name += "0";
        file_name.back() = symbol;
    }
    return file_name;
}

bool DearchiveFile(std::fstream& f, IStreamWrapper& input_stream, Trie& trie) {
    bool is_archive_ended = false;
    while (1) {
        uint16_t symbol = ReadOneSymbol(input_stream, trie);
        if (symbol == ARCHIVE_END || symbol == ONE_MORE_FILE) {
            f.close();
            if (symbol == ARCHIVE_END) {
                is_archive_ended = true;
            }
            break;
        }
        char to_print = symbol;
        f.write(&to_print, 1);
    }
    return is_archive_ended;
}

void Dearchive(IStreamWrapper& input_stream) {
    while (1) {                                                                 // dearchiving 1 file
        auto [symbol_count, symbols] = GetInfoForReconstructingCodes(input_stream);

        std::unordered_map<uint16_t, std::string> codes;
        ReconstructCanonicHuffmanCodes(symbol_count, symbols, codes, input_stream);

        Trie trie = Trie(codes);

        std::string file_name = DearchiveFileName(input_stream, trie);

        std::fstream f = std::fstream(file_name, std::ios_base::binary | std::ios_base::out);
        if (!f.is_open()) {
            throw std::invalid_argument("Cannot open file : " + file_name);
        }

        if (DearchiveFile(f, input_stream, trie)) {                   // If archive ended
            break;
        }
    }
}
