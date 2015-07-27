#if ! defined(fndivide_h)
#define fndivide_h

	#include "listable_numeric.h"

	class FunctionDivide : public ListableNumericFunction {
		protected:
			virtual EPtr first_argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                bool hasMore,
                State &callerState,
                bool &stop
            ) override;

			virtual EPtr argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) override;
	};

#endif
