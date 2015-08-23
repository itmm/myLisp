#if ! defined(listable_numeric_h)
#define listable_numeric_h

    #include "listable.h"

    class ListableNumericFunction : public ListableFunction {
		public:
			ListableNumericFunction(bool stopOnError = true) : ListableFunction(stopOnError) {}

		protected:
			virtual EPtr first_argument(
                EPtr intermediate,
                EPtr element,
                bool hasMore,
                State &callerState,
                bool &stop
            ) override;
        
			virtual EPtr argument(EPtr intermediate, EPtr element, State &callerState, bool &stop) override;
        
            virtual EPtr first_argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                bool hasMore,
                State &callerState,
                bool &stop
            );
        
            virtual EPtr argument_numeric(
                EPtr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) = 0;
    };

	/*TESTS:
	 *
     *  (assert (= (+ "a") (error "first argument must be numeric")))
	 *  (assert (= (+ 1 "a") (error "argument must be numeric")))
	 */

#endif
