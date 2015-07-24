#if !defined(listable_h)
#define listable_h

	#include "function.h"

	class Listable: public Function {
		public:
			Listable(bool stopOnError = true) : _stopOnError(stopOnError) {}

			virtual Ptr apply(Ptr arguments, State &state) override;

		protected:
			virtual Ptr empty_case(State &callerState);
			virtual Ptr setup(State &callerState, bool &stop);
			virtual Ptr first_argument(Ptr intermediate, Ptr element, bool hasMore, State &callerState, bool &stop);
			virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) = 0;
			virtual Ptr finish(Ptr intermediate, State &callerState);

		private:
			bool _stopOnError;
	};

#endif
