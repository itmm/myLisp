#include "pair.h"

Pair::~Pair() {
    // pairs are freed by the collector
    if (_car && !_car->as_pair()) { delete _car; } _car = nullptr;
    if (_cdr && !_cdr->as_pair()) { delete _cdr; } _cdr = nullptr;
}

Pair *Pair::as_pair() { return this; }

Pair *Pair::null() {
    static Pair instance(nullptr, nullptr);
    if (!instance._car) {
        
        // wouldn't it be great, if this test is only performed once and not on any access?
        
        instance._car = &instance;
        instance._cdr = &instance;
    }
    return &instance;
}
