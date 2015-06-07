#if !defined(function_h)
	#define function_h

	#include "element.h"

	class Function: public Element {
		public:
			virtual Function *as_function() override;
			virtual void to_stream(std::ostream &stream) const override;

			virtual Element *apply(Element *arguments);
	};

	/*TESTS:
	 *
	 *	Function().as_dictionary() == nullptr
	 *	Function().as_function() != nullptr
	 *	Function().as_number() == nullptr
	 *	Function().as_pair() == nullptr
	 *	Function().as_string() == nullptr
	 *
	 * 	Function().apply(nullptr) == nullptr
	 *
	 */

#endif
