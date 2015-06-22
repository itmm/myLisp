#include "dictionary.h"

#include "identifier.h"


void Dictionary::add_to_visit(Collector::Visitor &visitor) {
	visitor.add_to_visit(_parent);
	for (auto i = _map.begin(); i != _map.end(); ++i) {
		visitor.add_to_visit(i->second);
	}
}

Dictionary *Dictionary::as_dictionary() {
    return this;
}

void Dictionary::to_stream(std::ostream &stream) const {
    stream << "[Dictionary]";
}

Element *Dictionary::get(const std::string &key) {
    auto i = _map.find(key);
    if (i != _map.end()) {
        return i->second;
    } else if (_parent) {
        return _parent->get(key);
    } else {
        return nullptr;
    }
}

Element *Dictionary::get(Element *key) {
	if (Element::as_identifier(key)) {
		auto k = key->as_identifier()->str();
		Element *result = get(k);
		if (result || _map.find(k) != _map.end()) { return result; }
	}
	return key;
}

Dictionary *Dictionary::put(const std::string &key, Element *value) {
	_map[key] = value;
    return this;
}
