#if ! defined(fnfunction_h)
#define fnfunction_h

	#include "decider.h"

	class FunctionFunction : public Decider {
	protected:
		virtual bool is_valid(Element *element) override;
	};

#endif
