#include "pair.h"

Pair *Pair::_null = nullptr;


Pair::_SetupNull Pair::_setup;

Pair::_SetupNull::_SetupNull() {

    // setup null is tricky, because it points to itself
    
    _null = new Pair(nullptr, nullptr);
    _null->_car = _null;
    _null->_cdr = _null;
}

void Pair::free_children() {
    if (_car) { _car->free(); _car = nullptr; }
    if (_cdr) { _cdr->free(); _cdr = nullptr; }
}

Pair::~Pair() {
	free_children();
}

void Pair::free() {
    // free by garbage collector
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
            if (cur->car()) { stream << *cur->car(); }
            if (cur->cdr() && !cur->cdr()->as_pair()) {
                stream << " . " << *cur->cdr();
                break;
            }
            cur = cur->cdr() ? cur->cdr()->as_pair() : static_cast<Pair *>(nullptr);
        }
        stream << ")";
    }
}
