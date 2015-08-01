#include <iostream>
#include <fstream>

#include "fnprint.h"
#include "function.h"
#include "parser.h"
#include "stream_handler_std.h"

int main(int argc, const char * argv[]) {

    std::cout << "This is myLisp" << std::endl;

	State state; state.setName("root");
    dynamic_cast<FunctionPrint *>(state.root()->as_dictionary()->get("print"))->setHandler(new StreamHandlerStd(std::cout));
    dynamic_cast<FunctionPrint *>(state.root()->as_dictionary()->get("err-print"))->setHandler(new StreamHandlerStd(std::cerr));
    Parser parser(&state);
	std::cout << std::endl << "(import \"system.lsp\")" << std::endl;
	{
		std::ifstream system("system.lsp");
		for (; ;
			) {
			EPtr in = parser.parse(system);
			if (!in) { break; }
			state.eval(in);
		}
	}
	std::cout << "true" << std::endl << std::endl;

	for (;;) {
        EPtr in = parser.parse(std::cin);
        if (!in) { std::cout << "[# parse error #]" << std:: endl; break; }
		EPtr result = state.eval(in);
		std::cout << result << std::endl;
        state.collector()->collect();
    }
    
    return 0;
}
