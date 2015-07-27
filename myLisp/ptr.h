#if !defined(ptr_h)
#define ptr_h

/*
 *	Well, C++ is not good at garbage collection. This Ptr class assures, that
 *	collectible instances are marked as roots as long they are used in local
 *	variables.
 */

#include <cassert>
#include <iostream>

#include "collector.h"
#include "element.h"

class EPtr {
	public:
		EPtr(): _collector(nullptr), _value(nullptr) {}
		EPtr(Element *value, Collector *collector);
		EPtr(const EPtr &other);
		~EPtr();

		EPtr &operator=(const EPtr &other);

		Element &operator*() const { return *_value; }
		Element *operator->() const { return _value; }

		operator Element *() const { return _value; }
		operator bool() const { return _value != nullptr; }

	private:
		friend bool operator==(const EPtr &a, const EPtr &b);

		Collector *_collector;
		Element *_value;
};

inline EPtr::EPtr(Element *value, Collector *collector): _value(value), _collector(collector) {
	if (_value && _collector) _collector->add_root(_value);
}

inline EPtr::EPtr(const EPtr &other): _value(other._value), _collector(other._collector) {
	if (_value && _collector) _collector->add_root(_value);
}

inline EPtr::~EPtr() {
	if (_value && _collector) _collector->remove_root(_value);
}

inline EPtr &EPtr::operator=(const EPtr &other) {
	assert(_collector == other._collector || other._value == nullptr || _value == nullptr);
	if (_value && _collector) { _collector->remove_root(_value); } else { _collector = other._collector; }
	if (other._value && other._collector) { _collector = other._collector; _collector->add_root(other._value); }
	_value = other._value;
	return *this;
}

inline bool operator==(const EPtr &a, const EPtr &b) {
	if (a._collector != b._collector) { return false; }
	if (a._value == b._value) { return true; }
	if (!a._value || !b._value) { return false; }
	return a._value->is_equal(b._value);
}

inline bool operator!=(const EPtr &a, const EPtr &b) {
	return !(a == b);
}

std::ostream &operator<<(std::ostream &out, EPtr ptr);

#endif
