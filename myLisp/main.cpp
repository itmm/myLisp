#include <iostream>

#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

    Parser parser;
    for (;;) {
        Element *in = parser.parse(std::cin);
        if (!in) { break; }
        Element *out = in;
        std::cout << *out << std::endl;
    }
    
    return 0;
}
