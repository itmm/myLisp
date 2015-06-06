#if !defined(element_h)
#define element_h

    #include <iostream>

    class Number;
    class Pair;
    class String;

    class Element {
        public:
            Element() {}
            virtual ~Element();
        
            virtual Number *as_number();
            virtual Pair *as_pair();
            virtual String *as_string();
        
            virtual void to_stream(std::ostream &stream) const = 0;
        
        private:
            Element(const Element &);
            Element &operator=(const Element &);
    };

    inline std::ostream &operator<<(std::ostream &output, const Element &elm) {
        elm.to_stream(output);
        return output;
    }

#endif
