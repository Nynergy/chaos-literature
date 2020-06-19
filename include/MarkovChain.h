#pragma once

#include <unordered_map>
#include <unordered_set>

class MarkovChain {

public:
	std::unordered_map<std::string, std::unordered_set<std::string>> ngrams;
	std::unordered_set<std::string> beginnings;

	void addNgram(std::string prefix, std::string suffix);
	void addBeginning(std::string);

	std::string generateTitle();
	std::string generateSentence();
	std::string generateParagraph();

	void printNgrams();

private:
	std::string trim(const std::string & str);
	std::string removeChar(std::string str, char ch);
	std::string toTitleCase(std::string str);
	int randBetween(int min, int max);
	bool isHangingTitle(std::string lastWord);

};
