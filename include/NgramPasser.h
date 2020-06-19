#pragma once

#include "FileProcessor.h"
#include "MarkovChain.h"

class NgramPasser {

public:
	NgramPasser(MarkovChain * mkchainIn);
	void passNgrams(FileProcessor * fproc);

private:
	MarkovChain * mkchain;

};
