#if ! defined(fnstring_h)
#define fnstring_h

	#include "decider.h"

	class FunctionStringQuery : public Decider {
        protected:
            virtual bool is_valid(Element *element) override;
	};

#endif
