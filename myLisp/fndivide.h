#if ! defined(fndivide_h)
#define fndivide_h

	#include "listable.h"

	class FunctionDivide : public Listable {
		protected:
			virtual Ptr first_argument(Ptr intermediate, Ptr element, bool hasMore, State &callerState, bool &stop) override;

			virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;
	};

#endif
