#include "../include/tokens.h"

Tokens::Tokens() {}

void Tokens::addSentence(std::vector<Token*> sentence) {
	this->toks.push(sentence);
}

std::vector<Token*> Tokens::getSentence() {
	auto ret = this->toks.front();
	this->toks.pop();
	return ret;
}
