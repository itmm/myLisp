#ifndef number_h
#define number_h

    #include "element.h"
    #include "fractional.h"

    class Number : public Element {
        public:

            virtual Number *as_number();
            virtual void to_stream(std::ostream &output, bool escape) const override;
        
            const Fractional &value() const { return _value; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
            virtual bool is_less(Element *other) const override;

        protected:
			friend class Creator;

			Number(const Fractional &value): _value(value) {}

		private:
            Fractional _value;
	};

	/*TESTS:
	 *
	 *	(assert (= (true? 0) false) "true? 0")
	 *	(assert (= (true? 1) true) "true? 1")
	 *	(assert (= (true? -2/3) true) "true? -2/3")
	 *
	 *	(assert (= (dictionary? 0) false) "dictionary? 0")
	 *	(assert (= (error? -1) false) "error? -1")
	 *	(assert (= (function? 2) false) "function? 2")
	 *	(assert (= (identifier? 3) false) "identifier? 3")
	 *	(assert (= (number? 0) true) "number? 0")
	 *	(assert (= (number? -2/3) true) "number? -2/3")
	 *	(assert (= (number? infinity) true) "number? infinity")
	 *	(assert (= (number? (- infinity)) true) "number? -infinity")
	 *	(assert (= (number? not-a-number) true) "number? not a number")
	 *	(assert (= (pair? 2) false) "pair? 2")
	 *	(assert (= (string? 3) false) "string? 3")
	 *
	 *  (assert (= (str-print -2/3) "-2/3") "str-print -2/3")
	 */

#endif
