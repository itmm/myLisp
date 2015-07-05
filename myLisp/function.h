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

	/*C++-TESTS:
	 *
	 *	Function().as_dictionary() == nullptr
	 *	Function().as_function() != nullptr
	 *	Function().as_identifier() == nullptr
	 *	Function().as_number() == nullptr
	 *	Function().as_pair() == nullptr
	 *	Function().as_string() == nullptr
	 *
	 */

    /*C++-TESTS:
     *
     *+ State s;
     *
     *	Function().apply(Ptr(), s) == Ptr()
     *
     */

#endif
