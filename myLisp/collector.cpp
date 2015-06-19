#include "collector.h"

#include <cassert>

#include "creator.h"
#include "dictionary.h"

Collector::~Collector() {
    while (_initial_locks.size()) {
		remove_initial_lock(_initial_locks.front());
    }
    collect();
    assert(_managed.size() == 0);
}

void Collector::add_to_collector(Element *elm) {
	if (elm) {
		_initial_locks.push_back(elm);
		_managed.push_back(elm);
	}
}

void Collector::may_push_back(std::vector<Element *> &col, std::set<Element *> seen, Element *elm) {
    if (elm && elm != Pair::null()) {
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
        if (seen.find(*i) != seen.end()) {
            remaining.push_back(*i);
        } else {
            delete *i; *i = nullptr;
        }
    }
    _managed = remaining;
}
