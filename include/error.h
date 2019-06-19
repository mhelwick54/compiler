#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

#include "defines.h"

template <typename T>
void debug(std::string msg, T val) {
	if(DEBUG) {
		std::cout << msg << ": " << val << std::endl;
	}
}

void error(char const* file, int line, std::string msg, int err);

#define ERROR(MESSAGE, ERR) error(__FILE__, __LINE__, MESSAGE, ERR)

#endif //ERROR_H
