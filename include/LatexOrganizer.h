#pragma once

#include <fstream>

#include "MarkovChain.h"

class LatexOrganizer {

public:
	LatexOrganizer(MarkovChain * mkchainIn);
	void writeToFile();

private:
	MarkovChain * mkchain;
	std::ofstream outfile;

	std::string makeFriendly(std::string str);

};
