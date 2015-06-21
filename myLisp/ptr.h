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

class Ptr {
	public:
		Ptr(): _collector(nullptr), _value(nullptr) {}
		Ptr(Element *value, Collector *collector);
		Ptr(const Ptr &other);
		~Ptr();

		Ptr &operator=(const Ptr &other);

		Element &operator*() const { return *_value; }
		Element *operator->() const { return _value; }

		operator Element *() const { return _value; }
		operator bool() const { return _value != nullptr; }

	private:
		friend bool operator==(const Ptr &a, const Ptr &b);

		Collector *_collector;
		Element *_value;
};

inline Ptr::Ptr(Element *value, Collector *collector): _value(value), _collector(collector) {
	_collector->add_root(_value);
}

inline Ptr::Ptr(const Ptr &other): _value(other._value), _collector(other._collector) {
	_collector->add_root(_value);
}

inline Ptr::~Ptr() {
	_collector->remove_root(_value);
}

inline Ptr &Ptr::operator=(const Ptr &other) {
	assert(_collector == other._collector || other._value == nullptr);
	_collector->add_root(other._value);
	_collector->remove_root(_value);
	_value = other._value;
	return *this;
}

inline bool operator==(const Ptr &a, const Ptr &b) {
	return a._collector == b._collector && a._value == b._value;
}

inline bool operator!=(const Ptr &a, const Ptr &b) {
	return !(a == b);
}

std::ostream &operator<<(std::ostream &out, Ptr ptr);

#endif
