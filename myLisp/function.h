#if !defined(function_h)
	#define function_h

	#include "element.h"
	#include "creator.h"
    #include "state.h"

	class Function : public Element {
		public:
			virtual Function *as_function() override;
			virtual void to_stream(std::ostream &stream, bool escape) const override;

			virtual EPtr apply(EPtr arguments, State &state);
			virtual EPtr apply_evaled(EPtr arguments, State &state);
			virtual EPtr eval_arguments(EPtr arguments, State &state);
	};

	/*TESTS:
	 *
	 * 	(assert (= (true? +) false))
	 *
	 *	(assert (= (dictionary? +) false))
	 *	(assert (= (error? +) false))
	 *	(assert (= (function? +) true))
	 *	(assert (= (identifier? +) false))
	 *	(assert (= (number? +) false))
	 *	(assert (= (pair? +) false))
	 *	(assert (= (string? +) false))
	 */

#endif
