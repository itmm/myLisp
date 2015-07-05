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
	 *	(= (true? 0) false)
	 *	(= (true? 1) true)
	 *	(= (true? -2/3) true)
	 *
	 *	(= (dictionary? 0) false)
	 *	(= (error? -1) false)
	 *	(= (function? 2) false)
	 *	(= (identifier? 3) false)
	 *	(= (number? 0) true)
	 *	(= (number? -2/3) true)
	 *	(= (number? Infinity) true)
	 *	(= (number? (- Infinity)) true)
	 *	(= (number? NotANumber) true)
	 *	(= (pair? 2) false)
	 *	(= (string? 3) false)
	 *
	 *  (= (str-print -2/3) "-2/3")
	 */

#endif
