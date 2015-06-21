#include "ptr.h"
#include "element.h"

std::ostream &operator<<(std::ostream &out, Ptr ptr) {
	ptr->to_stream(out);
	return out;
}

