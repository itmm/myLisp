#include "dictionary.h"

#include "identifier.h"

bool Dictionary::is_true() const {
	if (_map.size()) { return true; }
	if (_parent && _parent->is_true()) { return true; }
	return false;
}

bool Dictionary::is_subset_of(const Dictionary *other) const {
	if (_parent && ! _parent->is_subset_of(other)) { return false; }
	for (auto i = _map.begin(); i != _map.end(); ++i) {
		if (! other || ! other->contains(i->first) || ! Element::is_equal(i->second, other->get(i->first))) {
            return false;
        }
	}
	return true;
}

bool Dictionary::is_equal(Element *other) const {
	if (Element::is_equal(other)) { return true; }
	Dictionary *otherDict = Element::as_dictionary(other);
	return otherDict && this->is_subset_of(otherDict) && otherDict->is_subset_of(this);
}

void Dictionary::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_parent);
	for (auto i = _map.begin(); i != _map.end(); ++i) {
		visitor.add_to_visit(i->second);
	}
}

Dictionary *Dictionary::as_dictionary() {
    return this;
}

void Dictionary::to_stream(std::ostream &stream, bool) const {
    std::string separator = "(dict (\"";
    for (const Dictionary *cur = this; cur; cur = cur->_parent) {
        for (auto i = cur->_map.begin(); i != cur->_map.end(); ++i) {
            stream << separator << i->first << "\" ";
            Element::to_stream(i->second, stream, true);
            stream << ")";
            separator = " (\"";
        }
    }
    if (separator == " (\"") {
        stream << ")";
    } else {
        stream << "(dict)";
    }
}

bool Dictionary::contains(const std::string &key) const {
	return _map.find(key) != _map.end() || (_parent && _parent->contains(key));
}

Element *Dictionary::get(const std::string &key) const {
    auto i = _map.find(key);
    if (i != _map.end()) {
        return i->second;
    } else if (_parent) {
        return _parent->get(key);
    } else {
        return nullptr;
    }
}

Element *Dictionary::get(Element *key) const {
	if (Element::as_identifier(key)) {
		auto k = key->as_identifier()->str();
		Element *result = get(k);
		if (result || _map.find(k) != _map.end()) { return result; }
        if (_parent) { return _parent->get(key); }
	}
	return key;
}

Dictionary *Dictionary::put(const std::string &key, Element *value) {
    for (Dictionary *current = this; current; current = current->parent()) {
        if (current->_map.find(key) != current->_map.end()) {
            current->_map[key] = value;
            return this;
        }
    }
	_map[key] = value;
    return this;
}

Dictionary *Dictionary::add(const std::string &key, Element *value) {
	_map[key] = value;
    return this;
}


std::map<std::string, Element *>::const_iterator Dictionary::begin() const {
	return _map.begin();
}

std::map<std::string, Element *>::const_iterator Dictionary::end() const {
	return _map.end();
}

bool Dictionary::is_less(Element *other) const {
    Dictionary *other_dict = Element::as_dictionary(other);
    if (! other_dict) return false;
    
    auto my_iter = _map.begin();
    auto my_end = _map.end();
    auto other_iter = other_dict->_map.begin();
    auto other_end = other_dict->_map.end();
    for (; my_iter != my_end && other_iter != other_end; ++my_iter, ++other_iter) {
        if (my_iter->first < other_iter->first) return true;
        if (other_iter->first < my_iter->first) return false;
        if (Element::is_less(my_iter->second, other_iter->second)) return true;
        if (Element::is_less(other_iter->second, my_iter->second)) return false;
    }
    if (my_iter != my_end) return false;
    return other_iter != other_end;
}
