#include "collector.h"

#include <cassert>

#include "dictionary.h"
#include "number.h"
#include "fnplus.h"

Collector::~Collector() {
    while (_initial_locks.size()) {
		release_initial_lock(_initial_locks.front());
    }
    collect();
    assert(_managed.size() == 0);
}

Pair *Collector::new_pair(Element *car, Element *cdr) {
    Pair *pair = new Pair(car, cdr);
    _initial_locks.push_back(pair);
    _managed.push_back(pair);
    return pair;
}

Dictionary *Collector::new_dictionary(Dictionary *parent) {
    Dictionary *dict = new Dictionary(parent);
    _initial_locks.push_back(dict);
    _managed.push_back(dict);
    return dict;
}

Dictionary *Collector::root_dictionary() {
    Dictionary *dict = new_dictionary();
    dict->put("Infinity", new Number(Fractional::infinity()));
    dict->put("NotANumber", new Number(Fractional::notANumber()));
	dict->put("+", new FunctionPlus());

    return dict;
}

void Collector::may_push_back(std::vector<Element *> &col, std::set<Element *> seen, Element *elm) {
    if (elm && elm != Pair::null() && (elm->as_pair() || elm->as_dictionary())) {
        if (seen.find(elm) == seen.end()) {
            col.push_back(elm);
        }
    }
}

void Collector::collect() {
    std::set<Element *> seen;
    std::vector<Element *> toVisit = _roots;
    toVisit.insert(toVisit.end(), _initial_locks.begin(), _initial_locks.end());
    
    while (toVisit.size()) {
        Element *cur = toVisit.back(); toVisit.pop_back();
        if (!cur->as_pair()) { continue; }
        if (seen.find(cur) != seen.end()) { continue; }
        seen.insert(cur);
        
        Pair *cur_pair = cur->as_pair();
        if (cur_pair && cur_pair != Pair::null()) {
            may_push_back(toVisit, seen, cur_pair->car());
            may_push_back(toVisit, seen, cur_pair->cdr());
        }
        
        Dictionary *cur_dict = cur->as_dictionary();
        if (cur_dict) {
            may_push_back(toVisit, seen, cur_dict->parent());
        }
    }
    
    std::vector<Element *> remaining;
    for (auto i = _managed.begin(); i != _managed.end(); ++i) {
        if (seen.find(*i) == seen.end()) {
            Pair *p = (**i).as_pair();
            if (p) { p->free_children(); }
            
            Dictionary *d = (**i).as_dictionary();
            if (d) { d->free_children(); }
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
}
