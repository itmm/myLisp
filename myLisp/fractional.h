#if !defined(fractional_h)
#define fractional_h

    #include <iostream>
    
    typedef unsigned long BigInt;

    class Fractional {
        public:
            Fractional(const BigInt &numerator, const BigInt &denomerator = 1, bool isNegative = false);
        
            static Fractional infinity() { return Fractional(1, 0); }
            static Fractional minusInfinity() { return Fractional(1, 0, true); }
            static Fractional notANumber() { return Fractional(0, 0); }
        
            const BigInt &numerator() const { return _numerator; }
            const BigInt &denomerator() const { return _denomerator; }
            bool isNegative() const { return _isNegative; }
        
        private:
            BigInt _numerator;
            BigInt _denomerator;
            bool _isNegative;
    };

    inline Fractional operator-(const Fractional &num) {
        return Fractional(num.numerator(), num.denomerator(), !num.isNegative());
    }

    inline BigInt gcd(BigInt a, BigInt b) {
        while (b) {
            BigInt r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    inline Fractional::Fractional(const BigInt &numerator, const BigInt &denomerator, bool isNegative) {
        if (!denomerator) {
            _denomerator = 0;
            _numerator = numerator ? 1 : 0;
            _isNegative = numerator ? isNegative : false;
        } else {
            BigInt g = gcd(numerator, denomerator);
            _numerator =  g ? numerator/g : 0;
            _denomerator = _numerator ? denomerator/g : 1;
            _isNegative = _numerator ? isNegative : false;
        }
    }

    Fractional operator-(const Fractional &a, const Fractional &b);

    inline Fractional operator+(const Fractional &a, const Fractional &b) {
        if (a.isNegative() != b.isNegative()) {
           return a - (-b);
        }
        
        return Fractional(a.numerator() * b.denomerator() + b.numerator() * a.denomerator(), a.denomerator() * b.denomerator(), a.isNegative());
    }

    inline Fractional operator-(const Fractional &a, const Fractional &b) {
        if (a.isNegative() != b.isNegative()) {
            return a + (-b);
        }
        
        if (a.numerator() * b.denomerator() < b.numerator() * a.denomerator()) {
            return -(b - a);
        }
        
        return Fractional(a.numerator() * b.denomerator() - b.numerator() * a.denomerator(), a.denomerator() * b.denomerator(), a.isNegative());
    }

    inline Fractional operator*(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.numerator(), a.denomerator() * b.denomerator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *  Fractional(6) / 3 == 2
     *  1 / Fractional(2) == Fractional(1, 2)
     *  -Fractional(3) / 6 == -Fractional(1, 2)
     */
    inline Fractional operator/(const Fractional &a, const Fractional &b) {
        return Fractional(a.numerator() * b.denomerator(), a.denomerator() * b.numerator(), a.isNegative() != b.isNegative());
    }

    /*TESTS:
     *
     *  (Fractional(3) == Fractional(3)) == true
     *  (Fractional(3) == Fractional(4)) == false
     *  (Fractional(3) == -Fractional(3)) == false
     *  (Fractional(0) == -Fractional(0)) == true
     *
     *  (Fractional(2, 3) == Fractional(4, 6)) == true
     *  (Fractional(2, 3) == -Fractional(2, 3)) == false
     *
     */
    inline bool operator==(const Fractional &a, const Fractional &b) {
        return a.isNegative() == b.isNegative() && a.numerator() == b.numerator() && a.denomerator() == b.denomerator();
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
                return a.numerator() * b.denomerator() > b.numerator() * a.denomerator();
            } else {
                return true;
            }
        } else {
            if (b.isNegative()) {
                return false;
            } else {
                return a.numerator() * b.denomerator() < b.numerator() * a.denomerator();
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
     *  (OUT << Fractional::minusInfinity()) == "-Infinity"
     *  (OUT << Fractional::notANumber()) == "NotANumber"
     *
     */
    std::ostream &operator<<(std::ostream &output, const Fractional &value);

#endif
