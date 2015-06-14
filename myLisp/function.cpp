#include "function.h"

Function *Function::as_function() {
	return this;
}

void Function::to_stream(std::ostream &stream) const {
	stream << "[#FUNCTION#]";
}

Ptr Function::apply(Ptr arguments, Creator *) {
	return arguments;
}

Ptr Function::eval_arguments(Ptr arguments, Creator *creator) {
	if (!arguments || !arguments->as_pair() || arguments == Ptr(Pair::null(), creator->collector())) {
		return arguments;
	}
	Pair *pair = arguments->as_pair();
	Ptr old_cdr = Ptr(pair->cdr(), creator->collector());
	Ptr old_car = Ptr(pair->car(), creator->collector());
	Ptr new_cdr = eval_arguments(old_cdr, creator);
	Ptr new_car = creator->eval(old_car);
	if (new_car != old_car || new_cdr != old_cdr) {
		return creator->new_pair(new_car, new_cdr);
	} else {
		return arguments;
	}
}