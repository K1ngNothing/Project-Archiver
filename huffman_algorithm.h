#pragma once

#include "archive.h"
#include "constants.h"
#include "heap.h"
#include "trie.h"
#include "vertex.h"

#include <algorithm>
#include <map>

std::pair<std::unordered_map<uint16_t, std::string>, std::vector<uint16_t>> HuffmanAlgorithm(
    std::unordered_map<uint16_t, size_t> count_of_symbols);

void AddOne(std::string& num);

void MakeNextCanonicCode(std::string& code, size_t length);
std::unordered_map<uint16_t, size_t> GetBasicCodes(std::unordered_map<uint16_t, size_t> count_of_symbols);