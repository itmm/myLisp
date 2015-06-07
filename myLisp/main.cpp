#include <iostream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

    Parser parser;
    for (;;) {
        Element *in = parser.parse(std::cin);
        if (!in) { break; }
        Element *out;
		Element *head = in && in->as_pair() ? in->as_pair()->car() : static_cast<Element *>(nullptr);
		if (head && head->as_function()) {
			out = head->as_function()->apply(in);
		} else {
			out = in;
		}
        std::cout << *out << std::endl;
    }
    
    return 0;
}
