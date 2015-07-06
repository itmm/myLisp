#if ! defined(lookbehind_h)
#define lookbehind_h

	#include "listable.h"

	class Lookbehind : public Listable {
		public:
			Lookbehind(): Listable(false) {}

		protected:
			virtual bool is_valid(Element *last, Element *current) = 0;

			virtual Ptr first_argument(Ptr intermediate, Element *element, bool hasMore, State &callerState, bool &stop) override;

			virtual Ptr argument(Ptr intermediate, Element *element, State &callerState, bool &stop) override;

			virtual Ptr finish(Ptr intermediate, State &callerState) override;
	};

#endif
