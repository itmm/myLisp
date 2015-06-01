#include "t_helper.h"

#include <sstream>

bool operator==(std::ostream &in, const char *expected) {
    bool result = ((std::ostringstream &) in).str() == expected;
    if (!result) {
        std::cerr << "got {" << ((std::ostringstream &) in).str() << "} instead of {" << expected << "}" << std::endl;
    }
    ((std::ostringstream &) in).str("");
    return result;
}
