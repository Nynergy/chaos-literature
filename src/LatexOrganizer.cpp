#include "LatexOrganizer.h"

LatexOrganizer::LatexOrganizer(MarkovChain * mkchainIn) : mkchain(mkchainIn) {
	outfile.open("Chaos.tex");
}

void LatexOrganizer::writeToFile() {
	// Memoir class document
	outfile << "\\documentclass[11pt, oneside, onecolumn]{memoir}" << std::endl;

	writeDocumentStyling();

	writeTitlePage();

	// Open document environment
	outfile << "\\begin{document}" << std::endl << std::endl;

	// Render title page
	outfile << "\\maketitle" << std::endl;

	// Randomly decide how many chapters to write
	int nbChapters = RandUtil::randBetween(3, 7);
	while(nbChapters > 0) {
		writeChapter();
		nbChapters--;
	}

	// Close document environment
	outfile << "\\end{document}" << std::endl;

	outfile.close();
}

void LatexOrganizer::writeDocumentStyling() {
	// Stock, trim, and page size
	outfile << "\\setstocksize{9in}{6in}" << std::endl;
	outfile << "\\settrimmedsize{9in}{6in}{*}" << std::endl;
	outfile << "\\settrims{0pt}{0pt}" << std::endl;

	// Typeblock and margin size
	outfile << "\\settypeblocksize{8in}{30pc}{*}" << std::endl;
	outfile << "\\setlrmargins{*}{*}{*}" << std::endl;
	outfile << "\\setulmargins{*}{*}{*}" << std::endl;

	// Header and footer lengths
	outfile << "\\setheadfoot{\\baselineskip}{\\baselineskip}" << std::endl;
	outfile << "\\setheaderspaces{*}{*}{*}" << std::endl;

	// Fix layout
	outfile << "\\checkandfixthelayout" << std::endl;

	// Custom chapter styles
	outfile << "\\renewcommand{\\chaptitlefont}{\\normalfont\\Large\\scshape}" << std::endl;
}

/*
 * NOTE: This simply writes the code that populates title page values.
 * The page is actually rendered in the document environment in the
 * writeToFile() method.
 */
void LatexOrganizer::writeTitlePage() {
	std::string title = makeFriendly(mkchain->generateTitle());

	// Construct title page
	outfile << "\\title{" << title << "}" << std::endl;
	outfile << "\\date{\\today}" << std::endl;
	outfile << "\\author{Mark O. V.}" << std::endl;
}

void LatexOrganizer::writeParagraph() {
	std::string paragraph = makeFriendly(mkchain->generateParagraph());

	outfile << paragraph << std::endl << std::endl;
}

void LatexOrganizer::writeSection() {
	std::string section = makeFriendly(mkchain->generateTitle());

	outfile << "\\section{" << section << "}" << std::endl << std::endl;

	// Decide on a random number of paragraphs
	int nbParagraphs = RandUtil::randBetween(3, 8);
	while(nbParagraphs > 0) {
		writeParagraph();
		nbParagraphs--;
	}
}

void LatexOrganizer::writeChapter() {
	std::string chapter = makeFriendly(mkchain->generateTitle());

	outfile << "\\chapter{" << chapter << "}" << std::endl << std::endl;

	// Decide on a random number of sections
	int nbSections = RandUtil::randBetween(2, 6);
	while(nbSections > 0) {
		writeSection();
		nbSections--;
	}
}

std::string LatexOrganizer::makeFriendly(std::string str) {
	// Escape underscores so latex doesn't complain about them
	std::size_t underscoreIndex = str.find("_");
	while(underscoreIndex != std::string::npos) {
		str.replace(underscoreIndex, std::string::npos, "\\_");
		underscoreIndex = str.find("_", underscoreIndex + 2);
	}

	// Escape dollar signs as well
	std::size_t dollarIndex = str.find("$");
	while(dollarIndex != std::string::npos) {
		str.replace(dollarIndex, std::string::npos, "\\$");
		dollarIndex = str.find("$", dollarIndex + 2);
	}

	// Escape ampersands as well
	std::size_t andIndex = str.find("&");
	while(andIndex != std::string::npos) {
		str.replace(andIndex, std::string::npos, "\\&");
		andIndex = str.find("&", andIndex + 2);
	}

	return str;
}
