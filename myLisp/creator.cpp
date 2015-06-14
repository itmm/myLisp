//
// Created by Timm on 13.06.15.
// Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#include "creator.h"

#include "dictionary.h"
#include "function.h"
#include "number.h"
#include "string.h"

Ptr Creator::new_dictionary(Dictionary *parent) {
	Element *result = new Dictionary(parent);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}

Ptr Creator::new_number(const Fractional &value) {
	Element *result = new Number(value);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}

Ptr Creator::new_pair(Element *car, Element *cdr) {
	Element *result = new Pair(car, cdr);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}

Ptr Creator::new_string(const std::string &value) {
	Element *result = new String(value);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}

Ptr Creator::eval(Ptr expression) {
	Pair *pair = Element::as_pair(expression);
	if (pair && pair != Pair::null()) {
		Function *fn = Element::as_function(pair->car());
		if (fn) {
			return fn->apply(expression, this);
		}
	}
	return expression;
}