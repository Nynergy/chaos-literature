#include <dirent.h>
#include <iostream>

#include "NgramPasser.h"

int main(int argc, char * argv[]) {

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
		return 1;
	}

	// Generate title
	std::string title = mkchain->generateTitle();
	std::cout << std::endl << title << std::endl;

	// Generate text
	for(int i = 0; i < 3; i++) {
		std::string paragraph = mkchain->generateParagraph();
		std::cout << std::endl << paragraph << std::endl;
	}

	delete mkchain;

	return 0;

}
