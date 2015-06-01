#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number: public Element {
        public:
            Number(const Fractional value): _value(value) {}
        
            virtual Number *as_number();
            virtual void to_stream(std::ostream &output);
        
            const Fractional &value() const { return _value; }
        
        private:
            Fractional _value;
    };

    /*TESTS:
     *
     *  Number(42).value() == 42
     *
     */

#endif
