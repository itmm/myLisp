//
// Created by Timm on 13.06.15.
// Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#include "creator.h"

#include "dictionary.h"
#include "identifier.h"
#include "number.h"
#include "pair.h"


Ptr Creator::new_element(Element *element) {
	return Ptr(_collector->add_to_collector(element), _collector);
}

Ptr Creator::new_dictionary(Dictionary *parent) {
	return new_element(new Dictionary(parent));
}

Ptr Creator::new_number(const Fractional &value) {
	return new_element(new Number(value));
}

Ptr Creator::new_identifier(const std::string &value) {
	return new_element(new Identifier(value));
}

Ptr Creator::new_pair(Element *car, Element *cdr) {
	return new_element(new Pair(car, cdr));
}

Ptr Creator::new_string(const std::string &value) {
	return new_element(new String(value));
}
