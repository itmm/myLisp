#if !defined(element_h)
#define element_h

    #include <iostream>

    class Function;
    class Dictionary;
    class Number;
    class Pair;
    class String;

    class Element {
        public:
            Element() {}
            virtual ~Element();

            virtual Dictionary *as_dictionary();
            virtual Function *as_function();
            virtual Number *as_number();
            virtual Pair *as_pair();
            virtual String *as_string();

			static Dictionary *as_dictionary(Element *elm);
			static Function *as_function(Element *elm);
			static Number *as_number(Element *elm);
			static Pair *as_pair(Element *elm);
			static String *as_string(Element *elm);

			virtual void to_stream(std::ostream &stream) const = 0;
        
        private:
            Element(const Element &) = delete;
            Element &operator=(const Element &) = delete;
    };

	inline std::ostream &operator<<(std::ostream &out, const Element *elm) {
		if (elm) {
			elm->to_stream(out);
		} else {
			out << "[# NULL #]";
		}
		return out;
	}

#endif
