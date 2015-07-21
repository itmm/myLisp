#if !defined(fractional_h)
#define fractional_h

    #include <iostream>
    
	#include "bigint.h"

    class Fractional {
        public:
            Fractional(const BigInt &numerator, const BigInt &denominator = 1, bool isNegative = false);
        
            static Fractional infinity() { return Fractional(1, 0); }
            static Fractional minusInfinity() { return Fractional(1, 0, true); }
            static Fractional notANumber() { return Fractional(0, 0); }
        
            const BigInt &numerator() const { return _numerator; }
            const BigInt &denominator() const { return _denominator; }
            bool isNegative() const { return _isNegative; }
        
        private:
            BigInt _numerator;
            BigInt _denominator;
            bool _isNegative;
    };

	/*C++-TESTS:
	 *
	 *	Fractional(2, 3).numerator() == BigInt(2)
	 *	Fractional(2, 3).denominator() == BigInt(3)
	 *	(-Fractional(3)).numerator() == BigInt(3)
	 *	Fractional::infinity().denominator() == BigInt(0)
	 */

    /*TESTS:
     *
     *	(= (- 2/3) -2/3)
     *	(= (- -2) 2)
     */
    inline Fractional operator-(const Fractional &num) {
        return Fractional(num.numerator(), num.denominator(), !num.isNegative());
    }

    /*C++-TESTS:
     *
     *  gcd(2, 6) == BigInt(2)
     *  gcd(6, 2) == BigInt(2)
     *  gcd(1, 1) == BigInt(1)
     *  gcd(8, 8) == BigInt(8)
     *  gcd(0, 3) == BigInt(0)
     *  gcd(3, 0) == BigInt(0)
     *  gcd(0, 0) == BigInt(0)
     */
    inline BigInt gcd(BigInt a, BigInt b) {
        if (!a || ! b) { return 0; }
        while (b) {
            BigInt r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    /*TESTS:
     *
     *	(= 8/4 2)
     *	(= -3/2 (- 3/2))
     */
    inline Fractional::Fractional(const BigInt &numerator, const BigInt &denominator, bool isNegative) {
        if (!denominator) {
            _denominator = 0;
            _numerator = numerator ? 1 : 0;
            _isNegative = numerator ? isNegative : false;
        } else {
            BigInt g = gcd(numerator, denominator);
            _numerator =  g ? numerator/g : BigInt(0);
            _denominator = _numerator ? denominator/g : BigInt(1);
            _isNegative = _numerator ? isNegative : false;
        }
    }

    Fractional operator-(const Fractional &a, const Fractional &b);

    /*TESTS:
     *
     *	(= (+ 5/2 3) 11/2)
     *	(= (+ -3 7) 4)
     *	(= (+ -3 -3) -6)
     *	(= (+ 3 -7) -4)
     * 	(= (+ 2/3 0) 2/3)
     * 	(= (+ 1/3 5/3) 2)
     * 	(= (+ 1/2 3/5) 11/10)
     */
    inline Fractional operator+(const Fractional &a, const Fractional &b) {
        if (a.isNegative() != b.isNegative()) {
           return a - (-b);
        }
        
        return Fractional(a.numerator() * b.denominator() + b.numerator() * a.denominator(), a.denominator() *
			b.denominator(), a.isNegative());
    }

    /*TESTS:
     *
     *	(= (- 5 3) 2)
     *	(= (- 8/3 2/3) 2)
     *	(= (- 1/3 4/3) -1)
     */
    inline Fractional operator-(const Fractional &a, const Fractional &b) {
        if (a.isNegative() != b.isNegative()) {
            return a + (-b);
        }
        
        if (a.numerator() * b.denominator() < b.numerator() * a.denominator()) {
            return -(b - a);
        }
        
        return Fractional(a.numerator() * b.denominator() - b.numerator() * a.denominator(), a.denominator() *
			b.denominator(), a.isNegative());
    }

    /*TESTS:
     *
     *	(= (* 2/3 5/7) 10/21)
     *	(= (* 3 2/3) 2)
     *	(= (* 3 Infinity) Infinity)
     *	(= (* 6 NotANumber) NotANumber)
     */
    inline Fractional operator*(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.numerator(), a.denominator() * b.denominator(), a.isNegative() != b.isNegative());
    }

    /*C++-TESTS:
     *
     *  Fractional(6) / BigInt(3) == BigInt(2)
     *  BigInt(1) / Fractional(2) == Fractional(1, 2)
     *  -Fractional(3) / BigInt(6) == -Fractional(1, 2)
     *  Fractional(1) / BigInt(0) == Fractional::infinity()
     *  -Fractional(1) / BigInt(0) == Fractional::minusInfinity()
     *  Fractional(0) / BigInt(0) == Fractional::notANumber()
     *
     */
    inline Fractional operator/(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.denominator(), a.denominator() * b.numerator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *	(= (= 3 3) true)
     *	(= (= 3 4) false)
     *	(= (= 3 -3) false)
     *	(= (= 0 -0) true)
     *
     *  (= (= 2/3 4/6) true)
     *  (= (= 2/3, -2/3) false)
     */
    inline bool operator==(const Fractional &a, const Fractional &b) {
        return a.isNegative() == b.isNegative() && a.numerator() == b.numerator() && a.denominator() == b.denominator();
    }

    /*TESTS:
     *
     *	(= (< 3 4) true)
     *	(= (< 4 3) false)
     *	(= (< 3 3) false)
     *	(= (< -3 3) true)
     *	(= (< 3 -4) false)
     *
     *	(= (< -3 -4) false)
     *	(= (< -4 -3) true)
     *	(= (< -3 -3) false)
     *	(= (< -0 0) false)
     *
     *	(= (< 3/5 4/5) true)
     *	(= (< 3/5 2/5) false)
     *	(= (< 3/5 3/4) true)
     *	(= (< 3/5 3/6) false)
     *	(= (< 3/5 4/6) true)
     *
     *	(= (< -3/5 -4/5) false)
     *	(= (< -3/5 -2/5) true)
     *	(= (< -3/5 -3/4) false)
     *	(= (< -3/5 -3/6) true)
     *	(= (< -3/5 -4/6) false)
     */
    inline bool operator<(const Fractional &a, const Fractional &b) {
        if (a.isNegative()) {
            if (b.isNegative()) {
                return b.numerator() * a.denominator() < a.numerator() * b.denominator();
            } else {
                return true;
            }
        } else {
            if (b.isNegative()) {
                return false;
            } else {
                return a.numerator() * b.denominator() < b.numerator() * a.denominator();
            }
        }
    }

    /*TESTS:
     *
     *	(= (str-print 42) "42")
     *	(= (str-print 2/3) "2/3")
     *	(= (str-print -2/3) "-2/3")
     *	(= (str-print -0/2) "0")
     *	(= (str-print Infinity) "Infinity")
     *	(= (str-print (- Infinity)) "(- Infinity)")
     *	(= (str-print NotANumber) "NotANumber")
     */
    std::ostream &operator<<(std::ostream &output, const Fractional &value);

#endif
