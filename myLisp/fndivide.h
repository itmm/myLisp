#if ! defined(fndivide_h)
#define fndivide_h

	#include "listable.h"

	class FunctionDivide : public Listable {
		protected:
			virtual Ptr first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) override;

			virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;
	};

#endif
