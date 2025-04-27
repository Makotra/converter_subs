#pragma once
#include "subtitle.h"

#include <fstream>
subtitle* add(std::ifstream& input_file, std::string& word);
template< typename T >
void parsing(std::ifstream& fileName, T& format);
