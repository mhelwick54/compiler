#include "../include/token.h"

std::ostream& operator<<(std::ostream& os, const Token& t) {
	if(t.type == TokenType::KEYWORD) {
		os << "Token: " << t.token << " Type: " << "keyword\n";
	} else if(t.type == TokenType::IDENTIFIER) {
		os << "Token: " << t.token << " Type: " << "identifier\n";
	} else if(t.type == TokenType::OPERATOR) {
		os << "Token: " << t.token << " Type: " << "operator\n";
	} else if(t.type == TokenType::SYMBOL) {
		os << "Token: " << t.token << " Type: " << "symbol\n";
	} else if(t.type == TokenType::VALUE) {
		os << "Token: " << t.token << " Type: value\n";
	} else {
		os << "Token: " << t.token << " Type: unkown\n";
	}
	//os << "Token: " << t.token << " Type: " << static_cast<int>(t.type) << "\n";
	return os;
}
