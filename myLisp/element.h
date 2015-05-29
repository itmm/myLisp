#if !defined(element_h)
#define element_h

    class Pair;

    class Element {
        public:
            Element() {}
            virtual ~Element();
        
            virtual Pair *as_pair();
        
        private:
            Element(const Element &);
            Element &operator=(const Element &);
    };

#endif
