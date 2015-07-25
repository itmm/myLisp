#include "bigint.h"

#include <iomanip>

BigInt::BigInt(const BigInt &other): _bigger(other._bigger ? new BigInt(*other._bigger) : static_cast<BigInt *>(nullptr)) {
	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		_values[i] = other._values[i];
	}
}

BigInt &BigInt::operator=(const BigInt &other) {
	if (this == &other) return *this;

	delete _bigger; _bigger = nullptr;
	if (other._bigger) _bigger = new BigInt(*other._bigger);
	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		_values[i] = other._values[i];
	}
	return *this;
}

BigInt::operator bool() const {
	if (_bigger && *_bigger) return true;
	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		if (_values[i]) return true;
	}
	return false;
}

BigInt BigInt::operator+(const BigInt &other) const {
	if (!*this) { return other; }
	if (!other) { return *this; }

    BigInt result;
    BigInt *last = nullptr;

    unsigned carry = 0;
    const BigInt *a = this;
    const BigInt *b = &other;
    while (carry || a || b) {
        BigInt *current = last ? new BigInt() : &result;
        if (last) { last->_bigger = current; }
        last = current;

        for (int i = 0; i < _BLOCK_SIZE; ++i) {
            if (a) carry += a->_values[i];
            if (b) carry += b->_values[i];
            current->_values[i] = carry % _MOD;
            carry /= _MOD;
        }
        if (a) a = a->_bigger;
        if (b) b = b->_bigger;
    }

    return result;
}


BigInt BigInt::normalize() const {
	if (!_bigger) return *this;

	BigInt normalized = _bigger->normalize();
	BigInt result;
	if (normalized) { result._bigger = new BigInt(normalized); }
	for (int i = 0; i < _BLOCK_SIZE; ++i) {
		result._values[i] = _values[i];
	}
	return result;
}

BigInt BigInt::operator-(const BigInt &other) const {
	if (!other) return *this;

	const BigInt *a = this;
	const BigInt *b = &other;
    unsigned carry = 0;

    BigInt result;
    BigInt *last = nullptr;

    while (carry || b) {
        if (!a) {
			std::cerr << "underflow" << std::endl;
			return BigInt(0);
        }

		BigInt *current = last ? new BigInt() : &result;
        if (last) { last->_bigger = current; }
        last = current;

        for (int i = 0; i < _BLOCK_SIZE; ++i) {
            if (b) carry += b->_values[i];
            if (carry <= a->_values[i]) {
                current->_values[i] = a->_values[i] - carry;
                carry = 0;
            } else {
                current->_values[i] = (a->_values[i] + _MOD - carry) % _MOD;
                carry = 1;
            }
        }
        if (b) b = b->_bigger;
        a = a->_bigger;
    }

    for (; a; a = a->_bigger) {
		BigInt *current = last ? new BigInt() : &result;
        if (last) { last->_bigger = current; }
        last = current;

        for (int i = 0; i < _BLOCK_SIZE; ++i) {
            current->_values[i] = a->_values[i];
        }
    }

    return result.normalize();
}


BigInt BigInt::shift() const {
	if (! *this) return BigInt();

    unsigned v = 0;
    const BigInt *cur = this;
    BigInt result;
    BigInt *last = nullptr;
    while (cur) {
    	BigInt *current = last ? new BigInt() : &result;
    	if (last) last->_bigger = current;
    	last = current;

        for (int i = 0; i < _BLOCK_SIZE; ++i) {
        	current->_values[i] = v;
        	v = cur->_values[i];
        }
        cur = cur->_bigger;
    }
    if (v) {
    	BigInt *current = last ? new BigInt() : &result;
    	if (last) last->_bigger = current;
    	current->_values[0] = v;
    }
    return result;
}

BigInt BigInt::operator*(const unsigned other) const {
	if (! *this) return *this;
	if (! other) return BigInt();

    unsigned long mult = 0;
    BigInt result;
    BigInt *last = nullptr;
    const BigInt *a = this;
    while (a || mult) {
        BigInt *current = last ? new BigInt() : &result;
        if (last) { last->_bigger = current; }
        last = current;

        for (int i = 0; i < _BLOCK_SIZE; ++i) {
            if (a) { mult += a->_values[i] * (unsigned long) other; }
            current->_values[i] = (unsigned int) (mult % _MOD);
            mult /= _MOD;
        }
        if (a) { a = a->_bigger; }
    }

    return result;
}

BigInt BigInt::operator*(const BigInt &other) const {
	if (! *this || ! other) return BigInt();

    BigInt result;
    BigInt shifted = *this;
    for (const BigInt *b = &other; b; b = b->_bigger) {
        for (int i = 0; i < _BLOCK_SIZE; ++i) {
            if (b->_values[i]) {
                BigInt tmp = shifted * b->_values[i];
                result = result + tmp;
            }
            shifted = shifted.shift();
        }
    }
    return result;
}

BigInt BigInt::unshift() const {
	BigInt result;
	BigInt *last = nullptr;
    for (const BigInt *cur = this; cur; cur = cur->_bigger) {
    	BigInt *current = last ? new BigInt() : &result;
    	if (last) last->_bigger = current;
    	last = current;
        for (int i = 1; i < _BLOCK_SIZE; ++i) {
            current->_values[i - 1] = cur->_values[i];
        }
        current->_values[_BLOCK_SIZE - 1] = cur->_bigger ? cur->_bigger->_values[0] : 0;
    }
    return result.normalize();
}

unsigned BigInt::factor(const BigInt &a, const BigInt &b) const {
    unsigned min = 1;
    unsigned max = _MOD - 1;
    while (max > 1 + min) {
        unsigned mid = (max + min)/2;
        BigInt tmp = b * mid;
        if (tmp == a) { return mid; }
        else if (tmp < a) {
            min = mid;
        } else {
            max = mid;
        }
    }
    return min;
}

BigInt BigInt::full_divide(const BigInt &a, const BigInt &b, BigInt *mod) const {
	if (! b) { std::cerr << "division by zero" << std::endl; return b; }
    if (! a) { if (mod) { *mod = BigInt(0); } return a; }
	if (b == BigInt(1)) { if (mod) { *mod = BigInt(0); } return a; }

	BigInt rest = a;
	BigInt result;
    if (b <= rest) {
        BigInt rest_shifted = b;
        BigInt result_shifted = 1;
        while (rest_shifted <= rest) {
            rest_shifted = rest_shifted.shift();
            result_shifted = result_shifted.shift();
        }
        while (b <= rest) {
            while (rest_shifted > rest) {
                rest_shifted = rest_shifted.unshift();
                result_shifted = result_shifted.unshift();
            }
            unsigned factor = this->factor(rest, rest_shifted);
            if (factor == 0) {
				std::cerr << "factor error" << std::endl;
                return BigInt();
            }
            BigInt tmp1 = rest_shifted * factor;
            BigInt tmp2 = rest - tmp1;
            rest = tmp2;
            tmp1 = result_shifted * factor;
            tmp2 = result + tmp1;
            result = tmp2;
        }
    }

    if (mod) { *mod = rest; }
    return result;
}


BigInt BigInt::operator/(const BigInt &other) const {
	BigInt result = full_divide(*this, other, nullptr);
	return result;
}

BigInt BigInt::operator%(const BigInt &other) const {
	BigInt result;
	full_divide(*this, other, &result);
	return result;
}

bool BigInt::operator==(const BigInt &other) const {
	bool biggerPresent = _bigger && *_bigger;
	bool otherBiggerPresent = other._bigger && *other._bigger;

	if (biggerPresent && otherBiggerPresent) {
		if (! *_bigger == *other._bigger) { return false; }
	}
	else if (biggerPresent || otherBiggerPresent) { return false; }

	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		if (_values[i] != other._values[i]) return false;
	}
	return true;
}

bool BigInt::operator<(const BigInt &other) const {
	bool biggerPresent = _bigger && *_bigger;
	bool otherBiggerPresent = other._bigger && *other._bigger;

	if (biggerPresent && otherBiggerPresent) {
		return *_bigger < *other._bigger;
	}
	else if (otherBiggerPresent) return true;
	else if (biggerPresent) return false;

	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		if (_values[i] < other._values[i]) return true;
		else if (other._values[i] < _values[i]) return false;
	}
	return false;
}

bool BigInt::write(std::ostream &out) const {
	bool wrote_something = false;
	if (_bigger) { wrote_something = _bigger->write(out); }
	for (int i = _BLOCK_SIZE - 1; i >= 0; --i) {
		if (_values[i] || wrote_something) {
			if (wrote_something) out << std::setfill('0') << std::setw(_WIDTH);
			out << _values[i];
			wrote_something = true;
		}
	}
	return wrote_something;
}
