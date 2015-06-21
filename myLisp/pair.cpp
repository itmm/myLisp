#include "pair.h"

Pair *Pair::_null = nullptr;


Pair::_SetupNull Pair::_setup;

Pair::_SetupNull::_SetupNull() {

    // setup null is tricky, because it points to itself
    
    _null = new Pair(nullptr, nullptr);
    _null->_car = _null;
    _null->_cdr = _null;
}

void Pair::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_car);
	visitor.add_to_visit(_cdr);
}

bool Pair::is_true() const {
	return this != null();
}

Pair *Pair::as_pair() { return this; }

void Pair::to_stream(std::ostream &stream) const {
    if (this == _null) {
        stream << "()";
    } else {
        stream << "(";
        Pair *cur = const_cast<Pair *>(this);
        while (cur && cur != _null) {
            if (cur != this) { stream << " "; }
            if (cur->car()) { stream << cur->car(); }
            if (cur->cdr() && !cur->cdr()->as_pair()) {
                stream << " . " << cur->cdr();
                break;
            }
            cur = cur->cdr() ? cur->cdr()->as_pair() : static_cast<Pair *>(nullptr);
        }
        stream << ")";
    }
}
