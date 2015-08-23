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
            void to_stream_without_parenthesis(std::ostream &stream, bool escape) const;

			virtual bool is_true() const override;

            virtual bool is_equal(Element *other) const override;

            virtual bool is_less(Element *other) const override;

        protected:
            Pair(Element *car, Element *cdr): _car(car), _cdr(cdr) {}

            virtual std::string head() const;
        
            bool is_equal_pair(Pair *other) const;
        
        private:
            friend class Creator;
            
            Element *_car;
            Element *_cdr;
    };

	/*TESTS:
	 *
	 *	(assert (= (true? (list)) false))
	 *	(assert (= (true? (list (list))) true))
	 *	(assert (= (true? (list 0)) true))
	 *
	 *  (assert (= (= (list) (list)) true))
	 *  (assert (= (= (list 1 2) (list 1 2)) true))
	 *  (assert (= (= (list 1 2) (list 1)) false))
	 *
	 *  (assert (= (< (list) (list 1)) true))
	 *  (assert (= (< (list 1) (list)) false))
	 *  (assert (= (< (list 2 3) (list 3 2)) true))
	 *  (assert (= (< (list 3 2) (list 2 3)) false))
	 *  (assert (= (< (list 2 3) (list 2 4)) true))
	 *
	 *	(assert (= (dictionary? (list 1)) false))
	 *	(assert (= (error? (list -1)) false))
	 *	(assert (= (function? (list +)) false))
	 *	(assert (= (identifier? (list "ab")) false))
	 *	(assert (= (number? (list 2)) false))
	 * 	(assert (= (pair? (list)) true))
	 * 	(assert (= (pair? (list false)) true))
	 * 	(assert (= (string? (list "a")) false))
	 *
	 *  (assert (= (str-print (list "a" "b")) "(\"a\" \"b\")"))
	 *  (assert (= (str-print (list)) "()"))
	 *  (assert (= (str-print (list "a" . "b")) "(\"a\" . \"b\")"))
	 */

#endif
