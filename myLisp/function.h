#if !defined(function_h)
	#define function_h

	#include "element.h"
	#include "creator.h"

	class Function: public Element {
		public:
			virtual Function *as_function() override;
			virtual void to_stream(std::ostream &stream) const override;

			virtual Ptr apply(Ptr arguments, Creator *creator);
			Ptr eval_arguments(Ptr arguments, Creator *creator);
	};

	/*TESTS:
	 *
	 *	Function().as_dictionary() == nullptr
	 *	Function().as_function() != nullptr
	 *	Function().as_number() == nullptr
	 *	Function().as_pair() == nullptr
	 *	Function().as_string() == nullptr
	 *	Function().apply(Ptr(), nullptr) == Ptr()
	 *
	 */

#endif
