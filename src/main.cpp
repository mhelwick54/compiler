#include "../include/main.h"

int main(int argc, char* argv[]) {
	if(argc < 2) {
		ERROR("usage: ./bin/compile [filename]", USAGEERROR);
	}
	
	if(!validateFile(argv[1])) {
		ERROR("invalid file", FILEERROR);
	}

	Lexer *lex = new Lexer();
	lex->lex(argv[1]);

	return 0;
}

bool validateFile(char *filename) {
	int len = strlen(filename);
	if(filename[len-2] != '.' || filename[len-1] != 'c') {
		return false;
	}

	return true;
}
