#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <cctype>

#include "../../include/error.h"
#include "token.h"
#include "tokens.h"
#include "../../include/defines.h"

typedef struct sentence {
	std::vector<Token*> toks;
} Sentence;

class Lexer {
private:
	Tokens tokens;
	std::vector<std::string> keywords;
	std::vector<std::string> operators;
public:
	Lexer();

	Tokens getTokens() { return this->tokens; }

	Token* tokenize(std::string str);
	bool isOperator(std::string str);
	bool isKeyword(std::string str);
	bool regex(std::string str, std::string reg);
	void stripWhiteSpace(std::string *str);
	void lex(char *filename);
};

#endif //LEXER_H
