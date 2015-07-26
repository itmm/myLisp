#if ! defined(fndivide_h)
#define fndivide_h

	#include "listable_numeric.h"

	class FunctionDivide : public ListableNumericFunction {
		protected:
			virtual Ptr first_argument_numeric(
                Ptr intermediate,
                const Fractional &element,
                bool hasMore,
                State &callerState,
                bool &stop
            ) override;

			virtual Ptr argument_numeric(
                Ptr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) override;
	};

#endif
