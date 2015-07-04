#include <iostream>
#include <fstream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl;

	State state; state.setName("root");
    Parser parser(&state);
	std::cout << std::endl << "(import \"system.lsp\")" << std::endl;
	{
		std::ifstream system("system.lsp");
		for (; ;
			) {
			Ptr in = parser.parse(system);
			if (!in) { break; }
			state.eval(in);
		}
	}
	std::cout << "true" << std::endl << std::endl;

	for (;;) {
        Ptr in = parser.parse(std::cin);
        if (!in) { std::cout << "[# parse error #]" << std:: endl; break; }
		Ptr result = state.eval(in);
		std::cout << result << std::endl;
    }
    
    return 0;
}
