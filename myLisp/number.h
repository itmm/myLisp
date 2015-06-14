#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number: public Element {
        public:

            virtual Number *as_number();
            virtual void to_stream(std::ostream &output) const;
        
            const Fractional &value() const { return _value; }

			friend class Creator;

        private:
			Number(const Fractional &value): _value(value) {}

            Fractional _value;
    };

    /*TESTS:
     *
     *  NUMBER(5)->as_function() == nullptr
     *  NUMBER(0)->as_dictionary() == nullptr
     *  NUMBER(1)->as_number() != nullptr
     *  NUMBER(2)->as_pair() == nullptr
     *  NUMBER(3)->as_string() == nullptr
     *  NUMBER(4)->as_number()->value() == 4
     *
     *  NUMBER(42)->value() == 42
     *
     *>	static Fractional minusTwoThirds = -Fractional(2, 3);
     *
     *  (OUT << NUMBER(minusTwoThirds)) == "-2/3"
     *
     */

#endif
