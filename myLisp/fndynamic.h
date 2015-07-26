#if !defined(fndynamic_h)
#define fndynamic_h

	#include "function.h"

	class FunctionDynamic: public Function {
		public:
			FunctionDynamic(Element *args, Element *body, bool macro, State &state): _args(args), _body(body), _macro(macro), _root(Element::as_dictionary(state.root())), _inserter(Element::as_dictionary(
				state.inserter()
			)) {}

			virtual void add_to_visit(Collector::Visitor &visitor) override;

			virtual Ptr apply(Ptr arguments, State &state) override;
		private:
			bool _macro;
			Element *_args;
			Element *_body;

			Dictionary *_root;
			Dictionary *_inserter;
	public:
		virtual void to_stream(std::ostream &stream, bool escape) const override;
	};

	/*TESTS:
	 *
	 *+	(defn ("f" "a" "b") (+ a b))
	 *+ (defm ("g" . "args") (apply + args))
	 *
	 *	(assert (= (f 2 3) 5) "f 2 3")
	 *	(assert (= (g 2 3) 5) "g 2 3")
	 *
	 *	(assert (= (f) (error "too few arguments")) "f")
	 *	(assert (= (g) 0) "g")
	 *
	 *	(assert (= (f 2) (error "too few arguments")) "f 2")
	 *  (assert (= (g 2) 2) "g 2")
	 *
	 *	(assert (= (f 2 3 4) (error "too many arguments")) "f 2 3 4")
	 *	(assert (= (g 2 3 4) 9) "g 2 3 4")
	 */

	/*TESTS:
	 *
	 *+ (defm ("f" "a" . "b") (+ a (apply + b)))
	 *
	 *	(assert (= (f 2 3 4) 9) "mixed with 2 3 4")
	 *	(assert (= (f 2) 2) "mixed with 2")
	 */
#endif
