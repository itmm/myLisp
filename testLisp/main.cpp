#include "t_test.h"

#include <iostream>

std::vector<Test> &all_tests() {
    static std::vector<Test> singleton;
    return singleton;
}

int main(int argc, char **argv) {
    for (auto i = all_tests().begin(); i != all_tests().end(); ++i) {
        (**i)();
    }
    std::cout << "run " << all_tests().size() << " tests\n";
}
