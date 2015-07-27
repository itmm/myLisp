#if !defined(listable_h)
#define listable_h

	#include "function.h"

	class ListableFunction: public Function {
		public:
			ListableFunction(bool stopOnError = true) : _stopOnError(stopOnError) {}

			virtual EPtr apply(EPtr arguments, State &state) override;

		protected:
			virtual EPtr empty_case(State &callerState);
			virtual EPtr setup(State &callerState, bool &stop);
			virtual EPtr first_argument(
                EPtr intermediate,
                EPtr element,
                bool hasMore,
                State &callerState,
                bool &stop
            );
			virtual EPtr argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) = 0;
			virtual EPtr finish(EPtr intermediate, State &callerState);

		private:
			bool _stopOnError;
	};

    /*TESTS:
     *
	 *  (assert (= (+ . 2) (error "Listable needs a plain list")) "+ . 2")
	 *  (assert (= (+ 1 . 2) (error "Listable needs a plain list")) "+ 1 . 2")
     */
     
#endif
