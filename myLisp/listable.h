#if !defined(listable_h)
#define listable_h

	#include "function.h"

	class Listable: public Function {
		protected:
			virtual Ptr empty_case(State &callerState);
			virtual Ptr setup(State &callerState, bool &stop);
			virtual Ptr first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop);
			virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) = 0;

	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

#endif
