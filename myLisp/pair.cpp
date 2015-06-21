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
