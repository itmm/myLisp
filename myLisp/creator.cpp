//
// Created by Timm on 13.06.15.
// Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#include "creator.h"

#include "dictionary.h"
#include "error.h"
#include "identifier.h"
#include "number.h"
#include "pair.h"


EPtr Creator::new_element(Element *element) {
	return EPtr(_collector->add_to_collector(element), _collector);
}


EPtr Creator::new_error(const std::string &message) {
	return new_element(new Error(message));
}

EPtr Creator::new_dictionary(Dictionary *parent) {
	return new_element(new Dictionary(parent));
}

EPtr Creator::new_number(const Fractional &value) {
	return new_element(new Number(value));
}

EPtr Creator::new_identifier(const std::string &value) {
	return new_element(new Identifier(value));
}

EPtr Creator::new_pair(Element *car, Element *cdr) {
	return new_element(new Pair(car, cdr));
}

EPtr Creator::new_string(const std::string &value) {
	return new_element(new String(value));
}
