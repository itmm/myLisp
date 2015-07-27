#include "lookbehind.h"

EPtr Lookbehind::first_argument(EPtr, EPtr element, bool hasMore, State &callerState, bool &stop) {
	if (!hasMore) {
		stop = true;
		return callerState.error("Lookbehind needs at least two arguments");
	}
	return EPtr(element, callerState.collector());
}

EPtr Lookbehind::argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) {
	if (!is_valid(intermediate, element)) {
		stop = true;
		return callerState.falseNumber();
	}
	return EPtr(element, callerState.collector());
}

EPtr Lookbehind::finish(EPtr, State &callerState) {
	return callerState.trueNumber();
}
