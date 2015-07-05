#if !defined(function_h)
	#define function_h

	#include "element.h"
	#include "creator.h"
#include "state.h"

	class Function: public Element {
		public:
			virtual Function *as_function() override;
			virtual void to_stream(std::ostream &stream) const override;

			virtual Ptr apply(Ptr arguments, State &state);

			virtual Ptr eval_arguments(Ptr arguments, State &state);
	};

	/*TESTS:
	 *
	 * 	(= (true? +) false)
	 *
	 *	(= (dictionary? +) false)
	 *	(= (error? +) false)
	 *	(= (function? +) true)
	 *	(= (identifier? +) false)
	 *	(= (number? +) false)
	 *	(= (pair? +) false)
	 *	(= (string? +) false)
	 */

#endif
