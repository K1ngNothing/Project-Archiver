#include "heap.h"
#include "trie.h"
#include "archive.h"
#include "dearchive.h"

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

void GivenIncorrectArguments() {
    std::cout << "Invalid launch of archiver. Use -h flag for more information.";
}

void GivenCFlag(int argc, char* argv[]) {
    std::string archive_name = argv[2];

    std::fstream f(archive_name, std::ios_base::binary | std::ios_base::out);
    if (!f.is_open()) {
        throw std::invalid_argument("Cannot open file : " + archive_name);
    }
    OStreamWrapper output_stream(f);

    const size_t id_of_the_first_file = 3;
    for (size_t i = id_of_the_first_file; i < static_cast<size_t>(argc); i++) {
        std::string file_name = argv[i];

        std::fstream s(file_name, std::ios_base::binary | std::ios_base::in);
        if (!s.is_open()) {
            throw std::invalid_argument("Cannot open file: " + file_name);
        }
        IStreamWrapper input_stream(s);

        Archive(file_name, input_stream, output_stream, (i == static_cast<size_t>(argc) - 1));
        s.close();
    }
    output_stream.Flush();
    f.close();
}

void GivenDFlag(char* argv[]) {
    std::string archive_name = argv[2];

    std::fstream s(archive_name, std::ios_base::binary | std::ios_base::in);
    if (!s.is_open()) {
        throw std::invalid_argument("Cannot open file: " + archive_name);
    }
    IStreamWrapper input_stream = IStreamWrapper(s);

    Dearchive(input_stream);
}

void GivenHFlag() {
    std::cout << "1. If you want to archive files, use tag -c file_name1, file_name2, ...\n"
                 "2. If you want to dearchive file, use tag -d archive_name\n"
                 "3. If you want to pop this text, use tag -h\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            GivenIncorrectArguments();
            return 0;
        } else if (argv[1] == std::string("-c")) {
            GivenCFlag(argc, argv);
            return 0;
        } else if (argv[1] == std::string("-d")) {
            GivenDFlag(argv);
            return 0;
        } else if (argv[1] == std::string("-h")) {
            GivenHFlag();
            return 0;
        } else {
            GivenIncorrectArguments();
            return 0;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}