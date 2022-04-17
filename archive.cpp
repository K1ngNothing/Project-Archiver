#include "archive.h"

void PrintCode(const std::string& code, OStreamWrapper& output_stream) {
    for (char c : code) {
        if (c == '1') {
            output_stream.Put1b(1);
        } else {
            output_stream.Put1b(0);
        }
    }
}

std::pair<std::unordered_map<size_t, size_t>, size_t> GetHelpingInfo(std::unordered_map<uint16_t, std::string>& codes) {
    std::unordered_map<size_t, size_t> cnt_of_length;
    size_t max_code_size = 0;
    for (const std::pair<uint16_t, std::string> kvp : codes) {
        size_t length = kvp.second.size();
        cnt_of_length[length]++;
        max_code_size = std::max<size_t>(max_code_size, length);
    }
    return {cnt_of_length, max_code_size};
}

void PrintArchivedFile(OStreamWrapper& output_stream, std::unordered_map<uint16_t, std::string>& codes,
                          const std::vector<uint16_t>& order, std::unordered_map<size_t, size_t>& cnt_of_length,
                          size_t max_code_size, const std::string& file_name, const std::vector<uint16_t>& file) {
    uint16_t cnt_symbols = order.size();

    output_stream.Put9b(cnt_symbols);                             // Printing information for decoding
    for (size_t i = 0; i < cnt_symbols; i++) {
        output_stream.Put9b(order[i]);
    }
    for (size_t length = 1; length <= max_code_size; length++) {
        output_stream.Put9b(cnt_of_length[length]);
    }

    for (char c : file_name) {                                    // Printing file name
        PrintCode(codes[c], output_stream);
    }
    PrintCode(codes[FILENAME_END], output_stream);

    for (uint16_t character : file) {                             // Printing file itself
        PrintCode(codes[character], output_stream);
    }
}

void Archive(const std::string& file_name, IStreamWrapper& input_stream, OStreamWrapper& output_stream,
             bool is_last_file) {                                 // Archiving 1 file
    std::unordered_map<uint16_t, size_t> count_of_symbols;
    for (char c : file_name) {
        count_of_symbols[c]++;
    }
    std::vector<uint16_t> file;
    while (1) {
        uint16_t symbol = input_stream.GetBits(8);
        if (symbol == END_OF_FILE) {
            auto [codes, order] = HuffmanAlgorithm(count_of_symbols);
            auto [cnt_of_length, max_code_size] = GetHelpingInfo(codes);

            PrintArchivedFile(output_stream, codes, order, cnt_of_length, max_code_size, file_name, file);

            if (is_last_file) {
                PrintCode(codes[ARCHIVE_END], output_stream);
            } else {
                PrintCode(codes[ONE_MORE_FILE], output_stream);
            }
            break;
        } else {
            count_of_symbols[symbol]++;
            file.push_back(symbol);
        }
    }
}