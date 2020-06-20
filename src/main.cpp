#include <dirent.h>
#include <iostream>

#include "LatexOrganizer.h"
#include "NgramPasser.h"

int main(int argc, char * argv[]) {

	// Check for arguments
	if(argc != 2) {
		std::cerr << "USAGE: ./markovbook [output flag]" << std::endl;
		return 1;
	}

	std::string outputFlag = argv[1];
	if(outputFlag == "-h" || outputFlag == "--help") {
		std::cout << "USAGE: ./markovbook X\nWhere X can be any of the following:" << std::endl;
		std::cout << "\t\t-h | --help: Display this help message" << std::endl;
		std::cout << "\t\t-s | --stdout: Send output to stdout (default)" << std::endl;
		std::cout << "\t\t-l | --latex: Send output to a formatted LaTeX file" << std::endl;
		return 0;
	}

	// Seed RNG
	srand(time(NULL));

	MarkovChain * mkchain = new MarkovChain();
	NgramPasser passer = NgramPasser(mkchain);

	// Loop through each file in the corpus directory
	// feeding it to the Markov chain
	const char * corpusPath = "corpus";
	DIR * dir;
	struct dirent * ent;
	if((dir = opendir(corpusPath)) != NULL) {
		while((ent = readdir(dir)) != NULL) {
			std::string filePath = ent->d_name;
			if(filePath == "." || filePath == "..") { continue; }

			FileProcessor * fproc = new FileProcessor("corpus/" + filePath);
			passer.passNgrams(fproc);
			delete fproc;
		}
		closedir(dir);
	} else {
		// Could not open directory
		std::cerr << "Could not open directory '" << corpusPath << "'." << std::endl;
		delete mkchain;
		return 1;
	}

	if(outputFlag == "-l" || outputFlag == "--latex") {
		// Generate latex file with markov chain
		LatexOrganizer organ = LatexOrganizer(mkchain);
		organ.writeToFile();
	} else {
		// Send output to stdout
		std::string title = mkchain->generateTitle();
		std::cout << std::endl << "    " << title << std::endl;
		std::cout << "=========================================================================" << std::endl << std::endl;

		std::string section1 = mkchain->generateTitle();
		std::cout << "\t" << section1 << std::endl << std::endl;

		std::string paragraph1 = mkchain->generateParagraph();
		std::string paragraph2 = mkchain->generateParagraph();
		std::cout << paragraph1 << std::endl << std::endl;
		std::cout << paragraph2 << std::endl << std::endl;

		std::string section2 = mkchain->generateTitle();
		std::cout << "\t" << section2 << std::endl << std::endl;

		std::string paragraph3 = mkchain->generateParagraph();
		std::string paragraph4 = mkchain->generateParagraph();
		std::string paragraph5 = mkchain->generateParagraph();
		std::cout << paragraph3 << std::endl << std::endl;
		std::cout << paragraph4 << std::endl << std::endl;
		std::cout << paragraph5 << std::endl << std::endl;
	}

	delete mkchain;

	return 0;

}
