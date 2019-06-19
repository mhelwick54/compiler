#include "../include/error.h"

void error(char const * file, int line, std::string msg, int err) {
	if(err < 0 && err > -10) {
		std::cout << "Critical error: " << msg << " (" << err << ")\n";
		exit(err);
	} else {
		std::cout << "Error: " << msg << " (" << err << ")\n";
	}
}
