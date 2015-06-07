#include "element.h"

Element::~Element() {}
void Element::free() { delete this; }

Function *Element::as_function() { return nullptr; }
Dictionary *Element::as_dictionary() { return nullptr; }
Number *Element::as_number() { return nullptr; }
Pair *Element::as_pair() { return nullptr; }
String *Element::as_string() { return nullptr; }
