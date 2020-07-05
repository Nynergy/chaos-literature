#include <iostream>

#include "MarkovChain.h"

void MarkovChain::addNgram(std::string prefix, std::string suffix) {
	// If prefix is an empty string or white space, do not add it
	prefix = trim(prefix);
	if(prefix == "" || prefix == " ") { return; }

	// If prefix doesn't exist in the map, make a new key-value pair
	auto it = ngrams.find(prefix);
	if(it != ngrams.end()) {
		// The prefix exists already, update its values
		std::unordered_set<std::string> suffixes = ngrams.at(prefix);
		suffixes.insert(suffix);

		ngrams.at(prefix) = suffixes;
	} else {
		// The prefix does not exist, so create a new set
		std::unordered_set<std::string> value = {suffix};
		std::pair<std::string, std::unordered_set<std::string>> ngram = {prefix, value};
		ngrams.insert(ngram);
	}
}

void MarkovChain::addBeginning(std::string begin) {
	// If begin is an empty string or white space, do not add it
	begin = trim(begin);
	if(begin == "" || begin == " ") { return; }

	beginnings.insert(begin);
}

std::string MarkovChain::generateTitle() {
	// Generate a sentence and cut it down to around 5 words
	std::string sentence = generateSentence();
	int nbWords = RandUtil::randBetween(2, 10);

	std::size_t index = sentence.find(" ");
	while(nbWords > 0 && index != std::string::npos) {
		index = sentence.find(" ", index + 1);
		nbWords--;
	}

	// Cut sentence at new index limit
	std::string title = sentence.substr(0, index);

	// If title contains hanging words that aren't desirable, cut them
	std::size_t lastSpace = title.find_last_of(' ');
	if(lastSpace != std::string::npos) {
		std::string lastWord = title.substr(lastSpace + 1);
		while(isHangingTitle(lastWord)) {
			title = title.substr(0, lastSpace);
			lastSpace = title.find_last_of(' ');
			if(lastSpace == std::string::npos) {
				break;
			} else {
				lastWord = title.substr(lastSpace + 1);
			}
		}
	}

	// Remove any stray punctuation or odd characters
	std::unordered_set<char> removables = {
		'.', ',', '"', '-', '_', '=', ';', ':'
	};
	for(auto & ch : removables) {
		title = removeChar(title, ch);
	}

	// Make title TitleCase
	title = toTitleCase(title);

	return title;
}

std::string MarkovChain::generateSentence() {
	// Randomly select a beginning
	auto randomIt = std::next(std::begin(beginnings), RandUtil::randBetween(0, beginnings.size()));
	std::string begin = *randomIt;
	
	// Begin walking the ngram chain until an endpoint is found
	std::string current = begin;
	std::string sentence = current;

	while(current != "") {
		if(ngrams.find(current) == ngrams.end()) { break; }

		std::unordered_set<std::string> suffixes = ngrams.at(current);
		randomIt = std::next(std::begin(suffixes), RandUtil::randBetween(0, suffixes.size()));
		std::string suffix = *randomIt;

		std::size_t index = current.find(" ");
		if(index == std::string::npos) {
			// Current is a single word
			current = suffix;
		} else {
			std::string first = current.substr(index + 1);
			current = first + " " + suffix;
		}

		sentence += (" " + suffix);
	}

	// Remove extra space at the end of sentences
	std::string finalChar = sentence.substr(sentence.size() - 1);
	while(finalChar == " ") {
		sentence = sentence.substr(0, sentence.size() - 1);
		finalChar = sentence.substr(sentence.size() - 1);
	}

	// Add period if necessary
	if(finalChar != ".") {
		sentence = sentence.substr(0, sentence.size() - 2);
		sentence += ".";
	}

	// If first character is not capitalized, capitalize it
	if(sentence.at(0) >= 'a' && sentence.at(0) <= 'z') {
		sentence.at(0) = sentence.at(0) + 'A' - 'a';
	}

	return sentence;
}

std::string MarkovChain::generateParagraph() {
	// Generate a number of sentences and concatenate them
	int nbSentences = RandUtil::randBetween(3, 7);
	
	std::string paragraph = "";
	while(nbSentences > 0) {
		std::string sentence = generateSentence();
		paragraph += (sentence + " ");
		nbSentences--;
	}

	// Remove trailing space from paragraph
	paragraph = trim(paragraph);

	return paragraph;
}

void MarkovChain::printNgrams() {
	std::cout << "PRINTING NGRAMS..." << std::endl << std::endl;
	for(auto kvPair : ngrams) {
		auto key = kvPair.first;
		auto values = kvPair.second;
		std::cout << "PREFIX: '" << key << "'; SUFFIXES: ";
		for(auto suffix : values) {
			std::cout << "'" << suffix << "', ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "PRINTING BEGINNINGS..." << std::endl << std::endl;
	for(auto ngram : beginnings) {
		std::cout << ngram << std::endl;
	}
}

std::string MarkovChain::trim(const std::string & str) {
	std::size_t first = str.find_first_not_of(' ');
	if(std::string::npos == first) {
		return str;
	}

	std::size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

std::string MarkovChain::removeChar(std::string str, char ch) {
	std::size_t index = str.find(ch);
	while(index != std::string::npos) {
		std::string first = str.substr(0, index);
		std::string second = str.substr(index + 1);
		str = first + second;
		index = str.find(ch);
	}

	return str;
}

std::string MarkovChain::toTitleCase(std::string str) {
	bool check = false;
	for(int i = 0; i < (int)str.length(); i++) {
		if(!check && (str.at(i) >= 'a' && str.at(i) <= 'z')) {
			// New word, so capitalize this letter
			str.at(i) = str.at(i) + 'A' - 'a';
		}

		if(str.at(i) != ' ') {
			// Still in the same word
			check = true;
		} else {
			// New word found
			check = false;
		}
	}

	return str;
}

bool MarkovChain::isHangingTitle(std::string lastWord) {
	std::unordered_set<std::string> hangers = {
		"of", "is", "a", "the", "by", "and", "or", "in", "be",
		"with", "for", "been", "that", "Mr", "Mrs", "Dr", "his",
		"was", "Was", "we", "to", "it", "as", "our", "they", "have",
		"also", "than", "had", "when", "at", "my", "but", "if",
		"she", "its", "has", "their", "any", "every", "would",
		"no", "where", "were", "so", "while", "he", "however",
		"from", "are", "I", "almost", "an", "who", "which"
	};

	for(auto & hanger : hangers) {
		if(lastWord == hanger) {
			return true;
		}
	}

	return false;
}
