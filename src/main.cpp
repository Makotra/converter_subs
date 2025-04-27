#include "parser.h"
#include "subtitle.h"

#include <fstream>
#include <iostream>
int main(int argc, char *argv[])
{
	std::ifstream input_file(argv[1]);
//		if (!input_file.is_open())
//		{
//			std::cerr << "Ошибка: не удалось открыть входной файл." << std::endl;
//			return 1;
//		}
	std::string word = argv[2];
	subtitle *sub = add(input_file, word);
	delete sub;
	return 0;
}
