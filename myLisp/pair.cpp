#include "pair.h"

Element *Pair::car(Element *cur) {
	if (!cur) { return nullptr; }
	Pair *pair = Element::as_pair(cur);
	if (!pair) { return nullptr; }
	return pair->car();
}

Element *Pair::cdr(Element *cur) {
	if (!cur) { return nullptr; }
	Pair *pair = Element::as_pair(cur);
	if (!pair) { return nullptr; }
	return pair->cdr();
}

void Pair::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_car);
	visitor.add_to_visit(_cdr);
}

bool Pair::is_true() const {
	return true;
}


bool Pair::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }
	Pair *otherPair = Element::as_pair(other);
	return otherPair && Element::is_equal(_car, otherPair->car()) && Element::is_equal(_cdr, otherPair->cdr());
}

bool Pair::is_less(Element *other) const {
    Pair *otherPair = Element::as_pair(other);
    if (!otherPair) return false;
    if (Element::is_less(_car, otherPair->car())) return true;
    if (! Element::is_equal(_car, otherPair->car())) return false;
    return Element::is_less(_cdr, otherPair->cdr());
}

Pair *Pair::as_pair() { return this; }

void Pair::to_stream(std::ostream &stream) const {
	stream << "(";
	Pair *cur = const_cast<Pair *>(this);
	while (cur) {
		if (cur != this) { stream << " "; }
		stream << cur->car();
		if (cur->cdr() && !cur->cdr()->as_pair()) {
			stream << " . " << cur->cdr();
			break;
		}
		cur = Element::as_pair(cur->cdr());
	}
	stream << ")";
}
