#include "../include/lexer.h"

Lexer::Lexer() {
	static const std::string keys[] { "auto",
				"break",
				"case",
				"char",
				"const",
				"continue",
				"default",
				"do",
				"double",
				"else",
				"enum",
				"extern",
				"float",
				"for",
				"goto",
				"if",
				"int",
				"long",
				"register",
				"return",
				"short",
				"signed",
				"sizeof",
				"static",
				"struct",
				"switch",
				"typedef",
				"union",
				"unsigned",
				"void",
				"volatile",
				"while"
			};
	for(auto i : keys) {
		this->keywords.push_back(i);
	}

	static const std::string ops[] { "+",
		"-",
		"*",
		"/",
		"%",
		"++",
		"--",
		"=",
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		"<<=",
		">>=",
		"&=",
		"^=",
		"|=",
		"==",
		"!=",
		"<",
		"<=",
		">",
		">=",
		"&",
		"&&",
		"|",
		"||",
		"^",
		"~",
		"<<",
		">>",
		"?",
		":"
	};
	for(auto i : ops) {
		this->operators.push_back(i);
	}
}

Token* Lexer::tokenize(std::string str) {
	auto ptr = str.begin();
	Token *tok = new Token();
	debug("tokenizing", NULL);
	if(isOperator(std::string(str.begin(), str.begin() + 1))) {
		int len = 1;
		debug("isOperator true", len);
		if(isOperator(std::string(str.begin(), str.begin() + 2))) {
			len = 2;
			debug("isOperator true", len);
			if(isOperator(std::string(str.begin(), str.begin() + 3))) {
				len = 3;
				debug("isOperator true", len);
			}
		}
		tok->setToken(std::string(str.begin(), str.begin() + len));
		tok->setType(TokenType::OPERATOR);
		return tok;
	}

	while(ptr != str.end()) {
		debug("not op", NULL);
		if(!isalnum(*ptr)) {
			if(*ptr == '\'' || *ptr == '\"') {
				debug("start", *ptr);
				auto endPtr = ptr + 1;
				while(*endPtr != *ptr) {
					debug("end", *endPtr);
					endPtr++;
				}
				tok->setToken(std::string(ptr, endPtr + 1));
				tok->setType(TokenType::VALUE);
				return tok;
			} else if((*ptr == ' ' || *ptr == '(' || *ptr == '{' || *ptr == ';') && ptr != str.begin()) {
				debug("found breaker", *ptr);
				tok->setToken(std::string(str.begin(), ptr));
				debug("string token", tok->getToken());
				if(isKeyword(tok->getToken())) {
					debug("isKeyword", true);
					tok->setType(TokenType::KEYWORD);
				} else if(isVariable(std::string(str.begin(), ptr))) {
					debug("isKeyword", false);
					debug("isVariable", true);
					tok->setType(TokenType::IDENTIFIER);
				} else {
					debug("isVariable", false);
					tok->setType(TokenType::VALUE);
				}
				return tok;
			} else {
				if(*ptr == '(' || *ptr == '{' || *ptr == ';' || *ptr == ')' || *ptr == '}') {
					debug("found symbol", *ptr);
					tok->setToken(std::string(ptr, ptr + 1));
					tok->setType(TokenType::SYMBOL);
					return tok;
				} else {
					return NULL;
				}
			}
		}
		ptr++;
	}

	return NULL;
}

bool Lexer::isOperator(std::string str) {
	for(auto i : this->operators) {
		debug(str, i);
		if(str == i) {
			return true;
		}
	}
	return false;
}

bool Lexer::isKeyword(std::string str) {
	for(auto i : this->keywords) {
		debug(str, i);
		if(str.compare(i) == 0) {
			return true;
		}
	}
	return false;
}

bool Lexer::isVariable(std::string str) {
	if(!isalpha(str[0]) && str[0] != '_') {
		return false;
	}
	for(auto c : str) {
		if(!isalnum(c) && c != '_') {
			return false;
		}
	}
	return true;
}

void Lexer::stripWhiteSpace(std::string *str) {
	while((*str)[0] == ' ' || (*str)[0] == '\t') {
		debug("erasing space", NULL);
		(*str).erase(0, 1);
	}
}

void Lexer::lex(char *filename) {
	std::ifstream file;
	file.open(filename);
	if(!file.is_open()) {
		std::string err = "failed to open file ";
		err += filename;
		ERROR(err, FILEERROR);
	}

	std::string str = "";
	while(getline(file, str)) {
		//std::cout << str << std::endl;

		Sentence *lexed = new Sentence();
		while(str.length() > 0) {
			stripWhiteSpace(&str);
			Token *token = tokenize(str);
			if(token) {
				std::cout << *token;
				lexed->toks.push_back(token);
				str.erase(0, token->getToken().length());
				debug("line", str);
			}
		}
		this->tokens.addSentence(lexed->toks);
	}
	for(int i =0; i < this->tokens.getCount(); ++i) {
		for(auto tok : this->tokens.getSentence()) {
			std::cout << tok;
		}
	}
}
