#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number: public Element {
        public:

            virtual Number *as_number();
            virtual void to_stream(std::ostream &output) const;
        
            const Fractional &value() const { return _value; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;

        protected:
			friend class Creator;

			Number(const Fractional &value): _value(value) {}

		private:
            Fractional _value;
	};

    /*TESTS:
     *
     *+ Creator c;
     *
     *  c.new_number(5)->as_function() == nullptr
     *  c.new_number(0)->as_dictionary() == nullptr
     *	c.new_number(8)->as_identifier() == nullptr
     *  c.new_number(1)->as_number() != nullptr
     *  c.new_number(2)->as_pair() == nullptr
     *  c.new_number(3)->as_string() == nullptr
     *  c.new_number(4)->as_number()->value() == 4
     *
     *  c.new_number(42)->as_number()->value() == 42
     *
     *>	static Fractional minusTwoThirds = -Fractional(2, 3);
     *
     *+ OutSink os;
     *
     *  (os << c.new_number(minusTwoThirds)) == "-2/3"
     *
     */

	/*LISP-TESTS:
	 *
	 *	(= (true? 0) false)
	 *	(= (true? 1) true)
	 *	(= (true? -2/3) true)
	 */
#endif
