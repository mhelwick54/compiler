#ifndef TOKENS_H
#define TOKENS_H

#include <vector>
#include <queue>

#include "token.h"
#include "../../include/defines.h"

class Tokens {
private:
	std::queue<std::vector<Token*>> toks;
	int 							sentence_count;
public:
	Tokens();

	void addSentence(std::vector<Token*> sentence);
	void incrCount() { this->sentence_count++; }
	void decCount() { this->sentence_count--; }
	int getCount() { return this->sentence_count; }
	std::vector<Token*> getSentence();
};

#endif //TOKENS_H
