#if ! defined(lookbehind_h)
#define lookbehind_h

	#include "listable.h"

	class Lookbehind : public Listable {
		public:
			Lookbehind(): Listable(false) {}

		protected:
			virtual bool is_valid(Element *last, Element *current) = 0;

			virtual EPtr first_argument(EPtr intermediate, EPtr element, bool hasMore, State &callerState, bool &stop) override;

			virtual EPtr argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) override;

			virtual EPtr finish(EPtr intermediate, State &callerState) override;
	};

#endif
