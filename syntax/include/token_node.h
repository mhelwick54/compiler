#ifndef TOKEN_NODE_H
#define TOKEN_NODE_H

#include "../../lexer/include/token.h"

class TokenNode {
private:
	Token* 		token;
	TokenNode* 	left;
	TokenNode* 	right;
}

#endif //TOKEN_NODE_H
