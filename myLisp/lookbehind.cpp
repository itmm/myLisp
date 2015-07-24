#include "lookbehind.h"

Ptr Lookbehind::first_argument(Ptr, Ptr element, bool hasMore, State &callerState, bool &stop) {
	if (!hasMore) {
		stop = true;
		return callerState.creator()->new_error("Lookbehind needs at least two arguments");
	}
	return Ptr(element, callerState.collector());
}

Ptr Lookbehind::argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) {
	if (!is_valid(intermediate, element)) {
		stop = true;
		return callerState.falseNumber();
	}
	return Ptr(element, callerState.collector());
}

Ptr Lookbehind::finish(Ptr, State &callerState) {
	return callerState.trueNumber();
}
