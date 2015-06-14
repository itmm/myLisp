#include <iostream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

    Parser parser;
    for (;;) {
        Ptr in = parser.parse(std::cin);
        if (!in) { break; }
		Element *head = (in && in->as_pair()) ? in->as_pair()->car() : static_cast<Element *>(nullptr);
		if (head && head->as_function()) {
			Ptr result = head->as_function()->apply(in, parser.creator());
			if (result) {
				std::cout << result << std::endl;
			} else {
				std::cout << "[# ERROR: can't evaluate " << in << " #]" << std::endl;
			}
		} else {
			std::cout << in << std::endl;
		}
    }
    
    return 0;
}
