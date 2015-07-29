#if ! defined(fnnumberq_h)
#define fnnumberq_h

	#include "decider.h"

	class FunctionNumberQuery : public Decider {
        protected:
            virtual bool is_valid(Element *element) override;
	};

#endif
