#if !defined(pair_h)
#define pair_h

    #include "element.h"
    
    class Pair: public Element {
        public:
            Element *car() const { return _car; }
            Element *cdr() const { return _cdr; }

			static Element *car(Element *cur);
			static Element *cdr(Element *cur);

			virtual void add_to_visit(Collector::Visitor &visitor) override;

			virtual Pair *as_pair();
            virtual void to_stream(std::ostream &stream) const;

			virtual bool is_true() const override;

        private:
            Pair(Element *car, Element *cdr): _car(car), _cdr(cdr) {}

            friend class Creator;
            
            Element *_car;
            Element *_cdr;
        
	public:
		virtual bool is_equal(Element *other) const override;
	};

    /*TESTS:
     *
     *> #include "String.h"
     *
     *> #define PAIR() c.new_pair(nullptr, nullptr)
     *
     *+ Creator c;
     *
     *	PAIR()->is_true() == true
     *
     *  PAIR()->as_function() == nullptr
     *  PAIR()->as_dictionary() == nullptr
     *  PAIR()->as_identifier() == nullptr
     *  PAIR()->as_pair() != nullptr
     *  PAIR()->as_number() == nullptr
     *  PAIR()->as_string() == nullptr
     *
     *  PAIR()->as_pair()->car() == nullptr
     *  PAIR()->as_pair()->cdr() == nullptr
     *
     *+ OutSink os;
     *
     *  (os << c.new_pair(c.new_string("a"), c.new_pair(c.new_string("b"), nullptr))) == "(\"a\" \"b\")"
     *  (os << static_cast<Pair *>(nullptr)) == "()"
     *  (os << c.new_pair(c.new_string("a"), c.new_string("b"))) == "(\"a\" . \"b\")"
     *
     */

#endif
