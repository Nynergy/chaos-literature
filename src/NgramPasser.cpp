#include "NgramPasser.h"

NgramPasser::NgramPasser(MarkovChain * mkchainIn) : mkchain(mkchainIn) {}

void NgramPasser::passNgrams(FileProcessor * fproc) {
	// Get lines from FileProcessor
	std::string line;
	while(!fproc->isEOF) {
		line = fproc->poll();

		// Split line into ngrams and suffixes
		std::string ngram, suffix;
		std::string remainder = line + " ";
		std::size_t firstIndex, secondIndex, thirdIndex;

		// Flag for finding beginnings
		bool beginning = true;

		do {
			// Find indices of first three spaces, if possible
			firstIndex = remainder.find(" ");
			secondIndex = remainder.find(" ", firstIndex + 1);
			thirdIndex = remainder.find(" ", secondIndex + 1);

			// If no first index was found, then prefix is too short
			// Continue on to next line of input file
			if(firstIndex == std::string::npos) {
				break;
			}

			// If no second index was found, then add without suffix
			if(secondIndex == std::string::npos) {
				ngram = remainder.substr(0, firstIndex);;
				mkchain->addNgram(ngram, "");
				if(beginning) {
					mkchain->addBeginning(ngram);
				}
				break;
			}
		
			// Substring out the prefix
			ngram = remainder.substr(0, secondIndex);
			
			// If no third index was found, then remainder is one word
			// So add the remainder as the suffix
			if(thirdIndex == std::string::npos) {
				suffix = remainder.substr(secondIndex + 1);
				mkchain->addNgram(ngram, suffix);
				if(beginning) {
					mkchain->addBeginning(ngram);
				}
				break;
			}

			// Substring out the suffix
			int nbChars = thirdIndex - secondIndex - 1;
			suffix = remainder.substr(secondIndex + 1, nbChars);
			mkchain->addNgram(ngram, suffix);
			if(beginning) {
				mkchain->addBeginning(ngram);
				beginning = false;
			}

			// Reset new remainder
			remainder = remainder.substr(firstIndex + 1);
		} while(remainder != " ");
	}
}
