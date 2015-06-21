#include "ptr.h"
#include "element.h"

std::ostream &operator<<(std::ostream &out, Ptr ptr) {
	if (ptr) {
		ptr->to_stream(out);
	} else {
		out << "()";
	}
	return out;
}

