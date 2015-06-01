#include "pair.h"

Pair *Pair::_null = nullptr;
Pair::_SetupNull Pair::_setup;

Pair::_SetupNull::_SetupNull() {

    // setup null is tricky, because it points to itself
    
    _null = new Pair(nullptr, nullptr);
    _null->_car = _null;
    _null->_cdr = _null;
}

Pair::~Pair() {

    // pairs are freed by the collector
    
    if (_car && !_car->as_pair()) { delete _car; } _car = nullptr;
    if (_cdr && !_cdr->as_pair()) { delete _cdr; } _cdr = nullptr;
}

Pair *Pair::as_pair() { return this; }

void Pair::to_stream(std::ostream &stream) {
    if (this == _null) {
        stream << "()";
    } else {
        stream << "(";
        Pair *cur = this;
        while (cur && cur != _null) {
            if (cur != this) { stream << " "; }
            if (cur->car()) { stream << *cur->car(); }
            if (cur->cdr() && !cur->cdr()->as_pair()) {
                stream << " . " << *cur->cdr();
                break;
            }
            cur = cur->cdr() ? cur->cdr()->as_pair() : nullptr;
        }
        stream << ")";
    }
}
