#if !defined(fnbool_h)
#define fnbool_h

	#include "decider.h"

	class FunctionBoolQuery : public Decider {
		public:
			FunctionBoolQuery(bool expected): _expected(expected) {}

		private:
			bool _expected;

		protected:
			virtual bool is_valid(Element *element) override;
	};

	/*TESTS:
	 *
	 *	(assert (= (true? true) true))
	 *	(assert (= (true? false) false))
	 *	(assert (= (false? true) false))
	 *	(assert (= (false? false) true))
	 *
	 *  (assert (= (true? 1 2 "ab") true))
	 *  (assert (= (false? 0 "") true))
	 *
	 *  (assert (= (true?) (error "Listable needs at least one argument")))
	 *  (assert (= (true? . 2) (error "Listable needs a plain list")))
	 *  (assert (= (true? 2 . 3) (error "Listable needs a plain list")))
	 */

#endif
