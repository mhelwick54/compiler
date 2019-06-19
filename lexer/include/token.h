#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <iostream>

#include "../../include/defines.h"

enum class TokenType {
	KEYWORD = 1,
	IDENTIFIER = 2,
	OPERATOR = 3,
	SYMBOL = 4,
	VALUE = 5
};

class Token {
private:
	std::string token;
	TokenType	type;
public:
	Token() {}
	Token(std::string token) {
		this->token = token;
	}
	Token(std::string token, TokenType type) {
		this->token = token;
		this->type = type;
	}

	void 		setToken(std::string token) { this->token = token; }
	void 		setType(TokenType type) { this->type = type; }
	std::string getToken() { return this->token; }
	TokenType 	getType() { return this->type; }

	friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

#endif //TOKEN_H
