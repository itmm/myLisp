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
	Ptr new_car = old_car;
	Pair *car_pair = old_car->as_pair();
	if (car_pair) {
		Element *car_car = car_pair->car();
		if (car_car) {
			Function *car_car_fn = car_car->as_function();
			if (car_car_fn) {
				new_car = car_car_fn->apply(old_car, creator);
			}
		}
	}
	if (new_car != old_car || new_cdr != old_cdr) {
		return creator->new_pair(new_car, new_cdr);
	} else {
		return arguments;
	}
}