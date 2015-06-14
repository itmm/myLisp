#include <iostream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

    Parser parser;
    for (;;) {
        Ptr in = parser.parse(std::cin);
        if (!in) { std::cout << "[# parse error #]" << std:: endl; break; }
		Ptr result = parser.creator()->eval(in);
		std::cout << result << std::endl;
    }
    
    return 0;
}
