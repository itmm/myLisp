#if !defined(string_h)
#define string_h

    #include <string>

    #include "element.h"

    class String: public Element {
        public:

            const std::string &str() const { return _str; }

			virtual bool is_true() const override;
			virtual bool is_equal(Element *other) const override;
            virtual bool is_less(Element *other) const override;

			virtual String *as_string();
            virtual void to_stream(std::ostream &stream, bool escape) const override;

			friend class Creator;

		protected:
			String(const std::string &str): _str(str) {}

		private:
            std::string _str;
    };

	/*TESTS:
	 *
	 *	(assert (= (true? "") false) "true? empty string")
	 *	(assert (= (true? " ") true) "true? space")
	 *	(assert (= (true? "0") true) "true? zero string")
	 *
	 *  (assert (= (= "ab" "ab") true) "= ab ab")
	 *
	 *  (assert (= (< "abc" "aca") true) "< abc aca")
	 *  (assert (= (< "A" "a") true) "< A a")
	 *  (assert (= (< "" "a") true) "< empty string a")
	 *  (assert (= (< "zz" "zza") true) "< zz zza")
	 *  (assert (= (< "b" "b ") true) "< b b")
	 *  (assert (= (< " b" "b") true) "< prefixed b b")
	 *
	 *	(assert (= (dictionary? "dict") false) "dictionary? str")
	 *	(assert (= (error? "err") false) "error? str")
	 *	(assert (= (function? "+") false) "function? str")
	 *	(assert (= (identifier? "ab") false) "identifier? str")
	 *	(assert (= (number? "0") false) "number? str")
	 * 	(assert (= (pair? "()") false) "pair? str")
	 * 	(assert (= (string? "9") true) "string? str")
	 * 	(assert (= (string? "") true) "string empty string")
	 *
	 *  (assert (= (str-print "x y") "x y") "str-print str")
	 *  (assert (= (str-print "") "") "str-print empty string")
	 */

#endif
