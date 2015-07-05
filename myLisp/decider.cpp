#include "decider.h"

Ptr Decider::setup(State &callerState, bool &stop) {
	return callerState.trueNumber();
}

Ptr Decider::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	if (Element::is_true(intermediate) && is_valid(element)) return intermediate;
	stop = true;
	return callerState.falseNumber();
}
