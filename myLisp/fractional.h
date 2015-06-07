#if !defined(fractional_h)
#define fractional_h

    #include <iostream>
    
    typedef unsigned long BigInt;

    class Fractional {
        public:
            Fractional(const BigInt &numerator, const BigInt &denominator = 1, bool isNegative = false);
        
            static Fractional infinity() { return Fractional(1, 0); }
            static Fractional minusInfinity() { return Fractional(1, 0, true); }
            static Fractional notANumber() { return Fractional(0, 0); }
        
            const BigInt &numerator() const { return _numerator; }
            const BigInt denominator() const { return _denomerator; }
            bool isNegative() const { return _isNegative; }
        
        private:
            BigInt _numerator;
            BigInt _denomerator;
            bool _isNegative;
    };

	/*TESTS:
	 *
	 *	Fractional(2, 3).numerator() == 2
	 *	Fractional(2, 3).denominator() == 3
	 *	(-Fractional(3)).numerator() == 3
	 *	Fractional::infinity().denominator() == 0
	 *
	 */

    /*TESTS:
     *
     *  -Fractional(2, 3) == Fractional(2, 3, true)
     *  -Fractional(2, 1, true) == 2
     *
     */
    inline Fractional operator-(const Fractional &num) {
        return Fractional(num.numerator(), num.denominator(), !num.isNegative());
    }

    /*TESTS:
     *
     *  gcd(2, 6) == 2
     *  gcd(6, 2) == 2
     *  gcd(1, 1) == 1
     *  gcd(8, 8) == 8
     *  gcd(0, 3) == 0
     *  gcd(3, 0) == 0
     *  gcd(0, 0) == 0
     *
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
     *  Fractional(8, 4) == 2
     *  Fractional(3, 2, true) == -Fractional(3, 2)
     *
     */
    inline Fractional::Fractional(const BigInt &numerator, const BigInt &denominator, bool isNegative) {
        if (!denominator) {
            _denomerator = 0;
            _numerator = numerator ? 1 : 0;
            _isNegative = numerator ? isNegative : false;
        } else {
            BigInt g = gcd(numerator, denominator);
            _numerator =  g ? numerator/g : 0;
            _denomerator = _numerator ? denominator /g : 1;
            _isNegative = _numerator ? isNegative : false;
        }
    }

    Fractional operator-(const Fractional &a, const Fractional &b);

    /*TESTS:
     *
     *  Fractional(5, 2) + 3 == Fractional(11, 2)
     *  -Fractional(3) + 7 == 4
     *  -Fractional(3) + -Fractional(3) == -Fractional(6)
     *  3 + -Fractional(7) == -Fractional(4)
     *  Fractional(2, 3) + 0 == Fractional(2, 3)
     *  Fractional(1, 3) + Fractional(5, 3) == 2
     *  Fractional(1, 2) + Fractional(3, 5) == Fractional(11, 10)
     *
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
     *  Fractional(5) - 3 == 2
     *  Fractional(8, 3) - Fractional(2, 3) == 2
     *  Fractional(1, 3) - Fractional(4, 3) == -Fractional(1)
     *
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
     *  Fractional(2, 3) * Fractional(5, 7) == Fractional(10, 21)
     *  Fractional(3) * Fractional(2, 3) == 2
     *  3 * Fractional::infinity() == Fractional::infinity()
     *  6 * Fractional::notANumber() == Fractional::notANumber()
     *
     */
    inline Fractional operator*(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.numerator(), a.denominator() * b.denominator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *  Fractional(6) / 3 == 2
     *  1 / Fractional(2) == Fractional(1, 2)
     *  -Fractional(3) / 6 == -Fractional(1, 2)
     *  Fractional(1) / 0 == Fractional::infinity()
     *  -Fractional(1) / 0 == Fractional::minusInfinity()
     *  Fractional(0) / 0 == Fractional::notANumber()
     *
     */
    inline Fractional operator/(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.denominator(), a.denominator() * b.numerator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *  (Fractional(3) == 3) == true
     *  (Fractional(3) == 4) == false
     *  (Fractional(3) == -Fractional(3)) == false
     *  (Fractional(0) == -Fractional(0)) == true
     *
     *  (Fractional(2, 3) == Fractional(4, 6)) == true
     *  (Fractional(2, 3) == -Fractional(2, 3)) == false
     *
     */
    inline bool operator==(const Fractional &a, const Fractional &b) {
        return a.isNegative() == b.isNegative() && a.numerator() == b.numerator() && a.denominator() == b.denominator();
    }

    /*TESTS:
     *
     *  (Fractional(3) < Fractional(4)) == true
     *  (Fractional(4) < Fractional(3)) == false
     *  (Fractional(3) < Fractional(3)) == false
     *  (-Fractional(3) < Fractional(3)) == true
     *  (Fractional(3) < -Fractional(4)) == false
     *
     *  (-Fractional(3) < -Fractional(4)) == false
     *  (-Fractional(4) < -Fractional(3)) == true
     *  (-Fractional(3) < -Fractional(3)) == false
     *  (-Fractional(0) < Fractional(0)) == false
     *
     *  (Fractional(3, 5) < Fractional(4, 5)) == true
     *  (Fractional(3, 5) < Fractional(2, 5)) == false
     *  (Fractional(3, 5) < Fractional(3, 4)) == true
     *  (Fractional(3, 5) < Fractional(3, 6)) == false
     *  (Fractional(3, 5) < Fractional(4, 6)) == true
     *
     *  (-Fractional(3, 5) < -Fractional(4, 5)) == false
     *  (-Fractional(3, 5) < -Fractional(2, 5)) == true
     *  (-Fractional(3, 5) < -Fractional(3, 4)) == false
     *  (-Fractional(3, 5) < -Fractional(3, 6)) == true
     *  (-Fractional(3, 5) < -Fractional(4, 6)) == false
     *
     */
    inline bool operator<(const Fractional &a, const Fractional &b) {
        if (a.isNegative()) {
            if (b.isNegative()) {
                return a.numerator() * b.denominator() > b.numerator() * a.denominator();
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
     *  (OUT << Fractional(42)) == "42"
     *  (OUT << Fractional(2, 3)) == "2/3"
     *  (OUT << Fractional(2, 3, true)) == "-2/3"
     *  (OUT << Fractional(0, 2, true)) == "0"
     *  (OUT << Fractional::infinity()) == "Infinity"
     *  (OUT << Fractional::minusInfinity()) == "(- Infinity)"
     *  (OUT << Fractional::notANumber()) == "NotANumber"
     *
     */
    std::ostream &operator<<(std::ostream &output, const Fractional &value);

#endif
