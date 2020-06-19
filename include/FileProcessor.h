#pragma once

#include <fstream>
#include <string>

class FileProcessor {

public:
	bool isEOF;

	FileProcessor(std::string inputFileIn);
	std::string poll();

private:
	std::string inputFile;
	std::ifstream infile;
	std::string line;

};
