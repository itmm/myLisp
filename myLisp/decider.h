#if !defined(decider_h)
#define decider_h

	#include "listable.h"

	class Decider: public Listable {
		protected:
			virtual Ptr setup(State &callerState, bool &stop) override;
			virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;

			virtual bool is_valid(Element *element) = 0;
	};


#endif
