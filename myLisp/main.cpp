#include <iostream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

	State state;
    Parser parser(&state);
    for (;;) {
        Ptr in = parser.parse(std::cin);
        if (!in) { std::cout << "[# parse error #]" << std:: endl; break; }
		Ptr result = state.eval(in);
		std::cout << result << std::endl;
    }
    
    return 0;
}
