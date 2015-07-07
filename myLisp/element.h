#if !defined(element_h)
#define element_h

    #include <iostream>
	#include "collector.h"

	class Function;
	class Error;
    class Dictionary;
	class Identifier;
    class Number;
    class Pair;
    class String;

    class Element {
        public:
            Element() {}
            virtual ~Element();

			virtual void add_to_visit(Collector::Visitor &visitor);

			virtual bool is_true() const;
			virtual bool is_equal(Element *other) const;
			virtual bool is_less(Element *other) const;

            virtual Dictionary *as_dictionary();
            virtual Error *as_error();
            virtual Function *as_function();
			virtual Identifier *as_identifier();
            virtual Number *as_number();
            virtual Pair *as_pair();
            virtual String *as_string();

			static bool is_true(Element *elm);
			static bool is_equal(Element *a, Element *b);
			static bool is_less(Element *a, Element *b);

			static Dictionary *as_dictionary(Element *elm);
			static Error *as_error(Element *elm);
			static Function *as_function(Element *elm);
			static Identifier *as_identifier(Element *elm);
			static Number *as_number(Element *elm);
			static Pair *as_pair(Element *elm);
			static String *as_string(Element *elm);

			virtual void to_stream(std::ostream &stream) const = 0;
        
        private:
            Element(const Element &) = delete;
            Element &operator=(const Element &) = delete;
    };

	inline bool Element::is_equal(Element *a, Element *b) {
		if (a == b) { return true; }
		if (!a || !b) { return false; }
		return a->is_equal(b);
	}

	inline std::ostream &operator<<(std::ostream &out, const Element *elm) {
		if (elm) {
			elm->to_stream(out);
		} else {
			out << "()";
		}
		return out;
	}

#endif
