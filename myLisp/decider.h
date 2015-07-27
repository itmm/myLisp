#if !defined(decider_h)
#define decider_h

	#include "listable.h"

	class Decider: public Listable {
		protected:
			virtual EPtr setup(State &callerState, bool &stop) override;
			virtual EPtr argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) override;

			virtual bool is_valid(Element *element) = 0;
	};


#endif
