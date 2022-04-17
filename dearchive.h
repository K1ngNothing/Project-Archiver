#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "constants.h"
#include "istream_wrapper.h"
#include "huffman_algorithm.h"
#include "ostream_wrapper.h"

void Dearchive(IStreamWrapper& input_stream);

uint16_t ReadOneSymbol(IStreamWrapper& input_stream, Trie& trie);
