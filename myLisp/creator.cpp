//
// Created by Timm on 13.06.15.
// Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#include "creator.h"

#include "dictionary.h"
#include "pair.h"

Ptr Creator::new_pair(Element *car, Element *cdr) {
	Element *result = new Pair(car, cdr);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}

Ptr Creator::new_dictionary(Dictionary *parent) {
	Dictionary *result = new Dictionary(parent);
	_collector->add_to_collector(result);
	return Ptr(result, _collector);
}
