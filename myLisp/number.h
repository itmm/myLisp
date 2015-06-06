#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number: public Element {
        public:
            Number(const Fractional &value): _value(value) {}
        
            virtual Number *as_number();
            virtual void to_stream(std::ostream &output) const;
        
            const Fractional &value() const { return _value; }
        
        private:
            Fractional _value;
    };

    /*TESTS:
     *
     *  Number(1).as_number() != nullptr
     *  Number(2).as_pair() == nullptr
     *  Number(3).as_string() == nullptr
     *  Number(4).as_number()->value() == 4
     *
     *  Number(42).value() == 42
     *  (OUT << Number(-Fractional(2, 3))) == "-2/3"
     *
     */

#endif
