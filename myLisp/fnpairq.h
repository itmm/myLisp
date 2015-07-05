#if !defined(fnpair_h)
#define fnpair_h

	#include "decider.h"

	class FunctionPairQuery: public Decider {
	protected:
		virtual bool is_valid(Element *element) override;
	};

#endif
