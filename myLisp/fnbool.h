#if !defined(fnbool_h)
#define fnbool_h

	#include "decider.h"

	class FunctionBool: public Decider {
		public:
			FunctionBool(bool expected): _expected(expected) {}

		private:
			bool _expected;

		protected:
			virtual bool is_valid(Element *element) override;
	};

	/*TESTS:
	 *
	 *	(= (true? true) true)
	 *	(= (true? false) false)
	 *	(= (false? true) false)
	 *	(= (false? false) true)
	 *
	 *  (= (true? 1 2 "ab") true)
	 *  (= (false? 0 "") true)
	 *
	 *  (= (true?) (error "Listable needs at least one argument"))
	 *  (= (true? . 2) (error "Listable needs a plain list"))
	 *  (= (true? 2 . 3) (error "Listable needs a plain list"))
	 */

#endif
