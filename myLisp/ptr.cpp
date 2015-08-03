#include "ptr.h"
#include "element.h"

std::ostream &operator<<(std::ostream &out, EPtr ptr) {
	if (ptr) {
		ptr->to_stream(out, true);
	} else {
		out << "()";
	}
	return out;
}

