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

			virtual bool is_true() const override;

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
     *	Pair::null()->is_true() == false
     *
     *  Pair::null()->as_function() == nullptr
     *  Pair::null()->as_dictionary() == nullptr
     *  Pair::null()->as_identifier() == nullptr
     *  Pair::null()->as_pair() != nullptr
     *  Pair::null()->as_number() == nullptr
     *  Pair::null()->as_string() == nullptr
     *  Pair::null()->as_pair() == Pair::null()
     *
     *  Pair::null()->car() == Pair::null()
     *  Pair::null()->cdr() == Pair::null()
     *
     *+ Creator c;
     *
     *	c.new_pair(Pair::null(), Pair::null())->is_true() == true
     *
     *+ OutSink os;
     *
     *  (os << c.new_pair(c.new_string("a"), c.new_pair(c.new_string("b"), Pair::null()))) == "(\"a\" \"b\")"
     *  (os << Pair::null()) == "()"
     *  (os << c.new_pair(c.new_string("a"), c.new_string("b"))) == "(\"a\" . \"b\")"
     *
     */

#endif
