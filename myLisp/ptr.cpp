#include "ptr.h"
#include "element.h"

std::ostream &operator<<(std::ostream &out, EPtr ptr) {
    Element::to_stream(ptr, out, true);
    return out;
}

