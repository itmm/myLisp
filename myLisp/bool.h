#if !defined(bool_h)
#define bool_h

	#include "number.h"

	class Bool: public Number {
		private:
			Bool(const Fractional &value): Number(value) {}

			friend class RootFactory;

	public:
		virtual void to_stream(std::ostream &output) const override;
	};

/*TESTS:
 *
 *>	#include "dictionary.h"
 *
 *	RootFactory().root()->as_dictionary()->get("true")->is_true() == true
 *	RootFactory().root()->as_dictionary()->get("false")->is_true() == false
 *
 *+ OutSink os;
 *
 *	(os << RootFactory().root()->as_dictionary()->get("true")) == "true"
 *	(os << RootFactory().root()->as_dictionary()->get("false")) == "false"
 *
 */

#endif
