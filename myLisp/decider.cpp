#include "decider.h"

EPtr Decider::setup(State &callerState, bool &stop) {
	return callerState.trueNumber();
}

EPtr Decider::argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) {
	if (Element::is_true(intermediate) && is_valid(element)) return intermediate;
	stop = true;
	return callerState.falseNumber();
}
