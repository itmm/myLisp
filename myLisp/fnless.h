#if ! defined(fnless_h)
#define fnless_h

	#include "lookbehind.h"

	class FunctionLess : public Lookbehind {
        protected:
            virtual bool is_valid(Element *last, Element *current) override;
	};

#endif
