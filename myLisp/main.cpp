#include <iostream>

#include "function.h"
#include "parser.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl << std::endl;

    Parser parser;
    for (;;) {
        Ptr in = parser.parse(std::cin);
        if (!in) { std::cout << "[# parse error #]" << std:: endl; break; }
		Pair *pair = in->as_pair();
		Element *head = pair ? pair->car() : static_cast<Element *>(nullptr);
		if (head) {
			Function *fn = head->as_function();
			if (fn) {
				Ptr result = fn->apply(in, parser.creator());
				if (result) {
					std::cout << result << std::endl;
				} else {
					std::cout << "[# ERROR: can't evaluate " << in << " #]" << std::endl;
				}
			} else {
				std::cout << "[# no function application: " << in << " #]" << std::endl;
			}
		} else {
			std::cout << "[# no list: " << in << " #]" << std::endl;
		}
    }
    
    return 0;
}
