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
	 *	(= (true? (list)) false)
	 *	(= (true? (list (list))) true)
	 *	(= (true? (list 0)) true)
	 *
	 *	(= (dictionary? (list 1)) false)
	 *	(= (error? (list -1)) false)
	 *	(= (function? (list +)) false)
	 *	(= (identifier? (list "ab")) false)
	 *	(= (number? (list 2)) false)
	 * 	(= (pair? (list)) true)
	 * 	(= (pair? (list false)) true)
	 * 	(= (string? (list "a")) false)
	 *
	 *  (= (str-print (list "a" "b")) "(a b)")
	 *  (= (str-print (list)) "()")
	 *  (= (str-print (list "a" . "b")) "(a . b)")
	 */

#endif
