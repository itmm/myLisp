#if ! defined(fnerrorq_h)
#define fnerrorq_h

	#include "decider.h"

	class FunctionErrorQuery : public Decider {
        protected:
            virtual bool is_valid(Element *element) override;
	};

#endif
