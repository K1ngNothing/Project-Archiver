#pragma once

#include <fstream>
#include <iostream>

#include "istream_wrapper.h"
#include "huffman_algorithm.h"
#include "ostream_wrapper.h"

void Archive(const std::string& file_name, IStreamWrapper& input_stream, OStreamWrapper& output_stream,
             bool is_last_file);