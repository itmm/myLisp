#include "element.h"

Element::~Element() {}

Number *Element::as_number() { return nullptr; }
Pair *Element::as_pair() { return nullptr; }
String *Element::as_string() { return nullptr; }
