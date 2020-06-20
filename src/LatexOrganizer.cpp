#include "LatexOrganizer.h"

LatexOrganizer::LatexOrganizer(MarkovChain * mkchainIn) : mkchain(mkchainIn) {
	outfile.open("Chaos.tex");
}

void LatexOrganizer::writeToFile() {
	// Gather material from Markov Chain
	std::string title = mkchain->generateTitle();

	std::string section1 = mkchain->generateTitle();

	std::string paragraph1 = makeFriendly(mkchain->generateParagraph());
	std::string paragraph2 = makeFriendly(mkchain->generateParagraph());

	std::string section2 = mkchain->generateTitle();

	std::string paragraph3 = makeFriendly(mkchain->generateParagraph());
	std::string paragraph4 = makeFriendly(mkchain->generateParagraph());
	std::string paragraph5 = makeFriendly(mkchain->generateParagraph());

	// Memoir class document
	outfile << "\\documentclass[11pt, oneside, onecolumn]{memoir}" << std::endl;

	// Stock, trim, and page size
	outfile << "\\setstocksize{9in}{6in}" << std::endl;
	outfile << "\\settrimmedsize{9in}{6in}{*}" << std::endl;
	outfile << "\\settrims{0pt}{0pt}" << std::endl;

	// Typeblock and margin size
	outfile << "\\settypeblocksize{8in}{30pc}{*}" << std::endl;
	outfile << "\\setlrmargins{*}{*}{*}" << std::endl;
	outfile << "\\setulmargins{*}{*}{*}" << std::endl;

	// Header and footer lengths
	outfile << "\\setheadfoot{0.5\\baselineskip}{\\baselineskip}" << std::endl;
	outfile << "\\setheaderspaces{*}{*}{*}" << std::endl;

	// Fix layout
	outfile << "\\checkandfixthelayout" << std::endl;

	// Custom chapter styles
	outfile << "\\renewcommand{\\chaptitlefont}{\\normalfont\\Large\\scshape}" << std::endl;

	// Construct title page
	outfile << "\\title{" << title << "}" << std::endl;
	outfile << "\\date{\\today}" << std::endl;
	outfile << "\\author{Mark O. V.}" << std::endl;

	// Open document environment
	outfile << "\\begin{document}" << std::endl << std::endl;

	// Render title page
	outfile << "\\maketitle" << std::endl;

	// Insert section 1 header
	outfile << "\\chapter{" << section1 << "}" << std::endl << std::endl;

	// Two paragraphs
	outfile << paragraph1 << std::endl << std::endl;
	outfile << paragraph2 << std::endl << std::endl;

	// Newpage
	outfile << "\\newpage" << std::endl << std::endl;

	// Insert section 2 header
	outfile << "\\chapter{" << section2 << "}" << std::endl << std::endl;

	// Three paragraphs
	outfile << paragraph3 << std::endl << std::endl;
	outfile << paragraph4 << std::endl << std::endl;
	outfile << paragraph5 << std::endl << std::endl;

	// Close document environment
	outfile << "\\end{document}" << std::endl;

	outfile.close();
}

std::string LatexOrganizer::makeFriendly(std::string str) {
	// Escape underscores so latex doesn't complain about them
	std::size_t underscoreIndex = str.find("_");
	while(underscoreIndex != std::string::npos) {
		str.replace(underscoreIndex, std::string::npos, "\\_");
		underscoreIndex = str.find("_", underscoreIndex + 2);
	}

	return str;
}
