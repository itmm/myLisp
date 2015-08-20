#if ! defined(bigint_h)
#define bigint_h

	#include <iostream>

	class BigInt {
		public:
			BigInt(unsigned long value = 0);
			BigInt(const BigInt &other);

			BigInt &operator=(const BigInt &other);

			bool write(std::ostream &out) const;

			operator bool() const;
			BigInt operator+(const BigInt &other) const;
			BigInt operator-(const BigInt &other) const;
			BigInt operator*(const unsigned other) const;
			BigInt operator*(const BigInt &other) const;
			BigInt operator/(const BigInt &other) const;
			BigInt operator%(const BigInt &other) const;
			bool operator==(const BigInt &other) const;
			bool operator<(const BigInt &other) const;
			bool operator<=(const BigInt &other) const { return !(other < *this); }
			bool operator>(const BigInt &other) const { return other < *this; }

            BigInt random() const;
            
			~BigInt() { if (_bigger) { delete _bigger; }}

		private:
			static const unsigned _MOD = 1000000000;
			static const int _WIDTH = 9;
			static const int _BLOCK_SIZE = 8;

			BigInt *_bigger;
			unsigned _values[_BLOCK_SIZE];

			BigInt normalize() const;
			BigInt shift() const;
			BigInt unshift() const;
			unsigned factor(const BigInt &a, const BigInt &b) const;
			BigInt full_divide(const BigInt &a, const BigInt &b, BigInt *mod) const;
	};

	inline std::ostream &operator<<(std::ostream &out, const BigInt &value) {
		if (!value.write(out)) out << 0;
		return out;
	}

	inline bool operator!=(const BigInt &a, const BigInt &b) {
		return !(a == b);
	}

#endif
