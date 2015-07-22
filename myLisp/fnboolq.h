#if !defined(fnbool_h)
#define fnbool_h

	#include "decider.h"

	class FunctionBoolQuery: public Decider {
		public:
			FunctionBoolQuery(bool expected): _expected(expected) {}

		private:
			bool _expected;

		protected:
			virtual bool is_valid(Element *element) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (true? true) true) "true? true")
	 *	(assert (= (true? false) false) "true? false")
	 *	(assert (= (false? true) false) "false? true")
	 *	(assert (= (false? false) true) "false? false")
	 *
	 *  (assert (= (true? 1 2 "ab") true) "true? multiple")
	 *  (assert (= (false? 0 "") true) "false? multiple")
	 *
	 *  (assert (= (true?) (error "Listable needs at least one argument")) "true? error")
	 *  (assert (= (true? . 2) (error "Listable needs a plain list")) "true? . 2")
	 *  (assert (= (true? 2 . 3) (error "Listable needs a plain list")) "true? 2 . 3")
	 */

#endif
