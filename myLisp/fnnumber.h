#if ! defined(fnnumber_h)
#define fnnumber_h

	#include "decider.h"

	class FunctionNumber : public Decider {
	protected:
		virtual bool is_valid(Element *element) override;
	};

#endif
