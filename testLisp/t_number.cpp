#include "t_number.h"

#include <cassert>
#include <sstream>

#include "t_helper.h"

#include "number.h"

void t_number_tests() {
std::ostringstream OUT;
assert(Number(42).value() == 42);
}
