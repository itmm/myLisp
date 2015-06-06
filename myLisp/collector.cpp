#include "collector.h"

#include <iostream>
#include <set>

#include "pair.h"

Pair *Collector::new_pair(Element *car, Element *cdr) {
    Pair *pair = new Pair(car, cdr);
    _initial_bondages.push_back(pair);
    _managed.push_back(pair);
    return pair;
}

void Collector::collect() {
    std::cout << "before collect: " << _managed.size() << " (roots == " << _roots.size() << ")\n";
    
    std::set<Element *> seen;
    std::vector<Element *> toVisit = _roots;
    toVisit.insert(toVisit.end(), _initial_bondages.begin(), _initial_bondages.end());
    
    while (toVisit.size()) {
        Element *cur = toVisit.back(); toVisit.pop_back();
        if (!cur->as_pair()) { continue; }
        if (seen.find(cur) != seen.end()) { continue; }
        seen.insert(cur);
        
        Pair *cur_pair = cur->as_pair();
        if (cur_pair && cur_pair != Pair::null()) {
            Pair *car = cur_pair->car() ? cur_pair->car()->as_pair() : nullptr;
            car = car != Pair::null() ? car : nullptr;
            Pair *cdr = cur_pair->cdr() ? cur_pair->cdr()->as_pair() : nullptr;
            cdr = cdr != Pair::null() ? cdr : nullptr;
            
            if (car && seen.find(car) == seen.end()) { toVisit.push_back(car); }
            if (cdr && seen.find(cdr) == seen.end()) { toVisit.push_back(cdr); }
        }
    }
    
    std::vector<Element *> remaining;
    for (auto i = _managed.begin(); i != _managed.end(); ++i) {
        if (seen.find(*i) == seen.end()) {
            Pair *p = (**i).as_pair();
            if (p) { p->free_childs(); }
        }
    }
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
