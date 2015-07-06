#include "lookbehind.h"

Ptr Lookbehind::first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) {
	if (!hasMore) {
		stop = true;
		return callerState.creator()->new_error("Lookbehind needs at least two arguments");
	}
	return Ptr(element, callerState.collector());
}

Ptr Lookbehind::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	if (!is_valid(intermediate, element)) {
		stop = true;
		return callerState.falseNumber();
	}
	return Ptr(element, callerState.collector());
}

Ptr Lookbehind::finish(Ptr intermediate, State &callerState) {
	return callerState.trueNumber();
}
