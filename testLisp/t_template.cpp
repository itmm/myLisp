#include "t_%NAME%.h"

#include <cassert>
#include <sstream>

#include "t_helper.h"

#include "%NAME%.h"

void t_%NAME%_tests() {
    std::ostringstream OUT;
%TESTS%
}
