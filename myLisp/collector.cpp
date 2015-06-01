#include "collector.h"

#include <iostream>
#include <set>

#include "pair.h"

Pair *Collector::new_pair(Element *car, Element *cdr) {
    Pair *pair = new Pair(car, cdr);
    _roots.push_back(pair);
    _managed.push_back(pair);
    return pair;
}

void Collector::collect() {
    std::cout << "before collect: " << _managed.size() << " (roots == " << _roots.size() << ")\n";
    
    std::set<Pair *> seen;
    std::vector<Pair *> toVisit = _roots;
    while (toVisit.size()) {
        Pair *cur = toVisit.back(); toVisit.pop_back();
        if (seen.find(cur) != seen.end()) { continue; }
        seen.insert(cur);
        
        Pair *car = cur->car() ? cur->car()->as_pair() : nullptr;
        car = car != Pair::null() ? car : nullptr;
        Pair *cdr = cur->cdr() ? cur->cdr()->as_pair() : nullptr;
        cdr = cdr != Pair::null() ? cdr : nullptr;
        
        if (car && seen.find(car) == seen.end()) { toVisit.push_back(car); }
        if (cdr && seen.find(cdr) == seen.end()) { toVisit.push_back(cdr); }
    }
    
    std::vector<Pair *> remaining;
    for (auto i = _managed.begin(); i != _managed.end(); ++i) {
        if (seen.find(*i) != seen.end()) {
            remaining.push_back(*i);
        } else {
            delete *i; *i = nullptr;
        }
    }
    _managed = remaining;
    
    std::cout << "after collect: " << _managed.size() << "\n";
}
