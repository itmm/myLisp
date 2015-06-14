#include "dictionary.h"

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

Dictionary *Dictionary::put(const std::string &key, Element *value) {
    if (value) {
        _map[key] = value;
    }
    return this;
}
