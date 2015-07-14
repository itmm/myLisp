#include "fnand.h"

Ptr FunctionAnd::empty_case(State &callerState) {
	return callerState.trueNumber();
}

Ptr FunctionAnd::setup(State &callerState, bool &stop) {
	return callerState.trueNumber();
}

Ptr FunctionAnd::argument(Ptr intermediate, Element *element, State &callerState, bool &stop) {
	if (Element::is_true(element)) {
		return intermediate;
	}
	stop = true;
	return Ptr(element, callerState.collector());
}
