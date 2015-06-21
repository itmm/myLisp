#include "collector.h"

#include <cassert>

#include "creator.h"
#include "dictionary.h"
#include "pair.h"

Collector::~Collector() {
    while (_initial_locks.size()) {
		remove_initial_lock(_initial_locks.front());
    }
    collect();
    assert(_managed.size() == 0);
}

Element *Collector::add_to_collector(Element *elm) {
	if (elm) {
		_initial_locks.push_back(elm);
		_managed.push_back(elm);
	}
	return elm;
}

Collector::Visitor::Visitor(std::vector<Element *> &to_visit, std::set<Element *> &seen): _to_visit(to_visit), _seen(seen) {
}

void Collector::Visitor::add_to_visit(Element *elm) {
	if (elm && _seen.find(elm) == _seen.end()) {
		_to_visit.push_back(elm);
	}
}

bool Collector::add_root(Element *root) {
	if (root) {
		_roots.push_back(root);
		remove_initial_lock(root);
		return true;
	}
	return false;
}

bool Collector::remove_root(Element *root) {
	if (!root) { return false; }
	auto i = std::find(_roots.begin(), _roots.end(), root);
	if (i != _roots.end()) {
		_roots.erase(i);
		return true;
	}
	return false;
}


void Collector::collect() {
    std::set<Element *> seen;
    std::vector<Element *> toVisit = _roots;
    toVisit.insert(toVisit.end(), _initial_locks.begin(), _initial_locks.end());

	Visitor visitor(toVisit, seen);
    while (toVisit.size()) {
        Element *cur = toVisit.back(); toVisit.pop_back();
        if (seen.find(cur) != seen.end()) { continue; }
        seen.insert(cur);

		cur->add_to_visit(visitor);
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
