#if ! defined(fnidentifierq_h)
#define fnidentifierq_h

	#include "decider.h"

	class FunctionIdentifierQuery : public Decider {
		virtual bool is_valid(Element *element) override;
	};

#endif
