#if !defined(pair_h)
#define pair_h

    #include "element.h"
    
    class Pair: public Element {
        public:
            Element *car() const { return _car; }
            Element *cdr() const { return _cdr; }
            
            static Pair *null() { return _null; }
            
            virtual Pair *as_pair();
            virtual void to_stream(std::ostream &stream) const;

        private:
            Pair(Element *car, Element *cdr): _car(car), _cdr(cdr) {}

            friend class Creator;
            
            Element *_car;
            Element *_cdr;
        
            class _SetupNull {
                public:
                    _SetupNull();
            };
        
            friend class _SetupNull;
        
            static Pair *_null;
            static _SetupNull _setup;
    };

    /*TESTS:
     *
     *> #include "String.h"
     *
     *  Pair::null()->as_function() == nullptr
     *  Pair::null()->as_dictionary() == nullptr
     *  Pair::null()->as_pair() != nullptr
     *  Pair::null()->as_number() == nullptr
     *  Pair::null()->as_string() == nullptr
     *  Pair::null()->as_pair() == Pair::null()
     *
     *  Pair::null()->car() == Pair::null()
     *  Pair::null()->cdr() == Pair::null()
     *
     *  (OUT << CONS(creator.new_string("a"), CONS(creator.new_string("b"), Pair::null()))) == "(\"a\" \"b\")"
     *  (OUT << Pair::null()) == "()"
     *  (OUT << CONS(creator.new_string("a"), creator.new_string("b"))) == "(\"a\" . \"b\")"
     *
     */

#endif
