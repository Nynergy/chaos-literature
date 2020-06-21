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

	void writeDocumentStyling();
	void writeTitlePage();
	void writeParagraph();
	void writeSection();
	void writeChapter();
	std::string makeFriendly(std::string str);

};
