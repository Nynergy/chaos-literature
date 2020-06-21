#include "LatexOrganizer.h"

LatexOrganizer::LatexOrganizer(MarkovChain * mkchainIn) : mkchain(mkchainIn) {
	outfile.open("Chaos.tex");
}

void LatexOrganizer::writeToFile() {
	// Memoir class document
	outfile << "\\documentclass[11pt, twoside, onecolumn]{memoir}" << std::endl;

	writeDocumentStyling();

	// Open document environment
	outfile << "\\begin{document}" << std::endl << std::endl;

	outfile << "\\raggedbottom" << std::endl << std::endl;

	// Render title page
	writeTitlePage();

	// Set page and chapter style
	std::string pageStyle = "ruled";
	outfile << "\\pagestyle{" << pageStyle << "}" << std::endl;

	std::string chapterStyle = "thatcher";
	outfile << "\\chapterstyle{" << chapterStyle << "}" << std::endl;

	// Write ToC
	outfile << "\\tableofcontents*" << std::endl << std::endl;

	// Randomly decide how many parts to write
	int nbParts = RandUtil::randBetween(3, 6);
	while(nbParts > 0) {
		writePart();
		nbParts--;
	}

	// Close document environment
	outfile << "\\end{document}" << std::endl;

	outfile.close();
}

void LatexOrganizer::writeDocumentStyling() {
	// Packages
	outfile << "\\usepackage[sc]{mathpazo}" << std::endl;
	outfile << "\\linespread{1.05}" << std::endl;
	outfile << "\\usepackage[T1]{fontenc}" << std::endl << std::endl;

	// Stock, trim, and page size
	outfile << "\\setstocksize{9in}{6in}" << std::endl;
	outfile << "\\settrimmedsize{9in}{6in}{*}" << std::endl;
	outfile << "\\settrims{0pt}{0pt}" << std::endl;

	// Typeblock and margin size
	outfile << "\\settypeblocksize{7.5in}{27pc}{*}" << std::endl;
	outfile << "\\setlrmargins{*}{*}{1.618}" << std::endl;
	outfile << "\\setulmargins{*}{*}{*}" << std::endl;

	// Header and footer lengths
	outfile << "\\setheadfoot{1.2\\baselineskip}{2\\baselineskip}" << std::endl;
	outfile << "\\setheaderspaces{*}{*}{*}" << std::endl;

	// Fix layout
	outfile << "\\checkandfixthelayout" << std::endl;

	// Custom ToC Style
	outfile << "\\renewcommand{\\contentsname}{Table of Contents}" << std::endl;

	// Custom part styles
	outfile << "\\renewcommand{\\partnamefont}{\\normalfont\\LARGE\\scshape}" << std::endl;
	outfile << "\\renewcommand{\\partnumfont}{\\normalfont\\LARGE\\scshape}" << std::endl;
	outfile << "\\renewcommand{\\parttitlefont}{\\normalfont\\LARGE\\scshape}" << std::endl;
	outfile << "\\renewcommand{\\midpartskip}{\\par\\hrulefill\\vspace{\\onelineskip}\\par}" << std::endl;

	// Custom section styles
	outfile << "\\setsecheadstyle{\\large\\bfseries\\centering}" << std::endl;
}

void LatexOrganizer::writeTitlePage() {
	std::string title = makeFriendly(mkchain->generateTitle());
	std::string subtitle = makeFriendly(mkchain->generateTitle());

	outfile << "\\thispagestyle{empty}" << std::endl << std::endl;

	outfile << "\\newlength\\drop" << std::endl;
	outfile << "\\makeatletter" << std::endl;
	outfile << "\\begingroup%" << std::endl;
	outfile << "\\setlength\\drop{0.2\\textheight}" << std::endl;
	outfile << "\\centering" << std::endl;
	outfile << "\\vspace*{\\drop}" << std::endl;
	outfile << "{\\Huge\\bfseries " << title << "}\\\\[\\baselineskip]" << std::endl;
	outfile << "{\\par\\hrulefill\\vspace{\\baselineskip}\\par}" << std::endl;
	outfile << "{\\scshape " << subtitle << "}\\\\[\\baselineskip]" << std::endl;
	outfile << "\\vfill" << std::endl;
	outfile << "{\\large\\scshape Mark O. Vega}\\par" << std::endl;
	outfile << "\\vfill" << std::endl;
	outfile << "{\\scshape \\@date}\\par" << std::endl;
	outfile << "\\vspace*{1.5\\drop}" << std::endl;
	outfile << "\\endgroup" << std::endl;
	outfile << "\\makeatother" << std::endl << std::endl;

	outfile << "\\newpage" << std::endl << std::endl;
}

void LatexOrganizer::writeParagraph() {
	std::string paragraph = makeFriendly(mkchain->generateParagraph());

	// Randomly decide on footnotes/margin notes
	int notes = RandUtil::randBetween(0, 100);
	if(notes < 25) {
		// Add a footnote to the end of the paragraph
		std::string footnote = makeFriendly(mkchain->generateSentence());

		outfile << paragraph << std::endl;

		outfile << "\\footnote{" << footnote << "}" << std::endl;
	} else if(notes < 40) {
		// Add a margin note to the page
		std::string margin = makeFriendly(mkchain->generateSentence());

		outfile << "\\marginpar{\\tiny{" << margin << "}}" << std::endl;

		outfile << paragraph << std::endl;
	} else {
		outfile << paragraph << std::endl;
	}

	outfile << std::endl;
}

void LatexOrganizer::writeSection() {
	std::string section = makeFriendly(mkchain->generateTitle());

	outfile << "\\section{" << section << "}" << std::endl << std::endl;

	// Decide on a random number of paragraphs
	int nbParagraphs = RandUtil::randBetween(3, 16);
	while(nbParagraphs > 0) {
		writeParagraph();

		// Randomly decide on inclusion of breaks
		int fancyBreak = RandUtil::randBetween(0, 100);
		if(fancyBreak < 25 && nbParagraphs > 1) {
			outfile << "\\fancybreak{{\\vspace*{\\onelineskip}}{* * *}{\\vspace*{\\onelineskip}}}" << std::endl << std::endl;
		}

		nbParagraphs--;
	}
}

void LatexOrganizer::writeChapter() {
	std::string chapter = makeFriendly(mkchain->generateTitle());

	outfile << "\\chapter{" << chapter << "}" << std::endl << std::endl;

	// Write an epigraph that appears before the first paragraph
	std::string epigraph = makeFriendly(mkchain->generateSentence());
	int year = RandUtil::randBetween(500, 2020);

	outfile << "\\epigraph{\"" << epigraph << "\"}{Anonymous, ca. " << year << "}" << std::endl << std::endl;

	// Decide on a random number of sections
	int nbSections = RandUtil::randBetween(2, 6);
	while(nbSections > 0) {
		writeSection();
		nbSections--;
	}
}

void LatexOrganizer::writePart() {
	std::string part = makeFriendly(mkchain->generateTitle());

	outfile << "\\part{" << part << "}" << std::endl << std::endl;

	// Decide on a random number of chapters
	int nbChapters = RandUtil::randBetween(3, 6);
	while(nbChapters > 0) {
		writeChapter();
		nbChapters--;
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
