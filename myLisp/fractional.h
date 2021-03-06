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

	/*TESTS:
	 *
	 *	(assert (= (numerator 2/3) 2))
	 *	(assert (= (denominator 2/3) 3))
	 *	(assert (= (numerator -3) 3))
	 *	(assert (= (denominator infinity) 0))
	 */

    /*TESTS:
     *
     *	(assert (= (- 2/3) -2/3))
     *	(assert (= (- -2) 2))
     */
    inline Fractional operator-(const Fractional &num) {
        return Fractional(num.numerator(), num.denominator(), !num.isNegative());
    }

    /*TESTS:
     *
     *	(assert (= (gcd 2 6) 2))
     *	(assert (= (gcd 6 2) 2))
     *	(assert (= (gcd 1 1) 1))
     *	(assert (= (gcd 8 8) 8))
     *	(assert (= (gcd 0 3) 0))
     *	(assert (= (gcd 3 0) 0))
     *	(assert (= (gcd 0 0) 0))
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
     *	(assert (= 8/4 2))
     *	(assert (= -3/2 (- 3/2)))
     */
    inline Fractional::Fractional(const BigInt &numerator, const BigInt &denominator, bool isNegative) {
        if (!denominator) {
            _denominator = 0;
            _numerator = numerator ? 1 : 0;
            _isNegative = numerator ? isNegative : false;
        } else {
            BigInt g = gcd(numerator, denominator);
            if (! g) {
            	_numerator = BigInt(0);
            	_denominator = BigInt(1);
            } else if (g == BigInt(1)) {
	            _numerator =  numerator;
    	        _denominator = denominator;
            } else {
            	_numerator =  numerator/g;
            	_denominator = denominator/g;
            }
            _isNegative = _numerator ? isNegative : false;
        }
    }

    Fractional operator-(const Fractional &a, const Fractional &b);

    /*TESTS:
     *
     *	(assert (= (+ 5/2 3) 11/2))
     *	(assert (= (+ -3 7) 4))
     *	(assert (= (+ -3 -3) -6))
     *	(assert (= (+ 3 -7) -4))
     * 	(assert (= (+ 2/3 0) 2/3))
     * 	(assert (= (+ 1/3 5/3) 2))
     * 	(assert (= (+ 1/2 3/5) 11/10))
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
     *	(assert (= (- 5 3) 2))
     *	(assert (= (- 8/3 2/3) 2))
     *	(assert (= (- 1/3 4/3) -1))
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
     *	(assert (= (* 2/3 5/7) 10/21))
     *	(assert (= (* 3 2/3) 2))
     *	(assert (= (* 3 infinity) infinity))
     *	(assert (= (* 6 not-a-number) not-a-number))
     */
    inline Fractional operator*(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.numerator(), a.denominator() * b.denominator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *	(assert (= (/ 6 3) 2))
     *	(assert (= (/ 1 2) 1/2))
     *	(assert (= (/ -3 6) -1/2))
     *	(assert (= (/ 1 0) infinity))
     *	(assert (= (/ -1 0) (- infinity)))
     *	(assert (= (/ 0 0) not-a-number))
     */
    inline Fractional operator/(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.denominator(), a.denominator() * b.numerator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *	(assert (= (= 3 3) true))
     *	(assert (= (= 3 4) false))
     *	(assert (= (= 3 -3) false))
     *	(assert (= (= 0 -0) true))
     *
     *  (assert (= (= 2/3 4/6) true))
     *  (assert (= (= 2/3, -2/3) false))
     */
    inline bool operator==(const Fractional &a, const Fractional &b) {
        return a.isNegative() == b.isNegative() && a.numerator() == b.numerator() && a.denominator() == b.denominator();
    }

    /*TESTS:
     *
     *	(assert (= (< 3 4) true))
     *	(assert (= (< 4 3) false))
     *	(assert (= (< 3 3) false))
     *	(assert (= (< -3 3) true))
     *	(assert (= (< 3 -4) false))
     *
     *	(assert (= (< -3 -4) false))
     *	(assert (= (< -4 -3) true))
     *	(assert (= (< -3 -3) false))
     *	(assert (= (< -0 0) false))
     *
     *	(assert (= (< 3/5 4/5) true))
     *	(assert (= (< 3/5 2/5) false))
     *	(assert (= (< 3/5 3/4) true))
     *	(assert (= (< 3/5 3/6) false))
     *	(assert (= (< 3/5 4/6) true))
     *
     *	(assert (= (< -3/5 -4/5) false))
     *	(assert (= (< -3/5 -2/5) true))
     *	(assert (= (< -3/5 -3/4) false))
     *	(assert (= (< -3/5 -3/6) true))
     *	(assert (= (< -3/5 -4/6) false))
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
     *	(assert (= (str-print 42) "42"))
     *	(assert (= (str-print 2/3) "2/3"))
     *	(assert (= (str-print -2/3) "-2/3"))
     *	(assert (= (str-print -0/2) "0"))
     *	(assert (= (str-print infinity) "infinity"))
     *	(assert (= (str-print (- infinity)) "(- infinity)"))
     *	(assert (= (str-print not-a-number) "not-a-number"))
     */
    std::ostream &operator<<(std::ostream &output, const Fractional &value);

#endif
