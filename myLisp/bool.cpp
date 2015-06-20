//
// Created by Timm on 20.06.15.
// Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#include "bool.h"

void Bool::to_stream(std::ostream &output) const {
	output << (is_true() ? "true" : "false");
}
