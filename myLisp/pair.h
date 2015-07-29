#if !defined(pair_h)
#define pair_h

    #include "element.h"
    
    class Pair : public Element {
        public:
            Element *car() const { return _car; }
            Element *cdr() const { return _cdr; }

			static Element *car(Element *cur);
			static Element *cdr(Element *cur);

			virtual void add_to_visit(Collector::Visitor &visitor) override;

			virtual Pair *as_pair();
            virtual void to_stream(std::ostream &stream, bool escape) const override;

			virtual bool is_true() const override;

            virtual bool is_equal(Element *other) const override;

            virtual bool is_less(Element *other) const override;

        private:
            Pair(Element *car, Element *cdr): _car(car), _cdr(cdr) {}

            friend class Creator;
            
            Element *_car;
            Element *_cdr;
    };

	/*TESTS:
	 *
	 *	(assert (= (true? (list)) false) "true? ()")
	 *	(assert (= (true? (list (list))) true) "true? (())")
	 *	(assert (= (true? (list 0)) true) "true? (0)")
	 *
	 *  (assert (= (= (list) (list)) true) "= () ()")
	 *  (assert (= (= (list 1 2) (list 1 2)) true) "= (1 2) (1 2)")
	 *  (assert (= (= (list 1 2) (list 1)) false) "= (1 2) (1)")
	 *
	 *  (assert (= (< (list) (list 1)) true) "< () (1)")
	 *  (assert (= (< (list 1) (list)) false) "< (1) ()")
	 *  (assert (= (< (list 2 3) (list 3 2)) true) "< (2 3) (3 2)")
	 *  (assert (= (< (list 3 2) (list 2 3)) false) "< (3 2) (2 3)")
	 *  (assert (= (< (list 2 3) (list 2 4)) true) "< (2 3) (2 4)")
	 *
	 *	(assert (= (dictionary? (list 1)) false) "dictionary? (1)")
	 *	(assert (= (error? (list -1)) false) "error? (-1)")
	 *	(assert (= (function? (list +)) false) "function? (+)")
	 *	(assert (= (identifier? (list "ab")) false) "identifier? (ab)")
	 *	(assert (= (number? (list 2)) false) "number? (2)")
	 * 	(assert (= (pair? (list)) true) "pair? ()")
	 * 	(assert (= (pair? (list false)) true) "pair? (false)")
	 * 	(assert (= (string? (list "a")) false) "string? (a)")
	 *
	 *  (assert (= (str-print (list "a" "b")) "(\"a\" \"b\")") "str-print (\"a\" \"b\")")
	 *  (assert (= (str-print (list)) "()") "str-print ()")
	 *  (assert (= (str-print (list "a" . "b")) "(\"a\" . \"b\")") "str-print (\"a\" . \"b\")")
	 */

#endif
