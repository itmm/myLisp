#if ! defined(listable_numeric_h)
#define listable_numeric_h

    #include "listable.h"

    class ListableNumericFunction : public Listable {
		public:
			ListableNumericFunction(bool stopOnError = true) : Listable(stopOnError) {}

		protected:
			virtual Ptr first_argument(
                Ptr intermediate,
                Ptr element,
                bool hasMore,
                State &callerState,
                bool &stop
            ) override;
        
			virtual Ptr argument(Ptr intermediate, Ptr element, State &callerState, bool &stop) override;
        
            virtual Ptr first_argument_numeric(
                Ptr intermediate,
                const Fractional &element,
                bool hasMore,
                State &callerState,
                bool &stop
            );
        
            virtual Ptr argument_numeric(
                Ptr intermediate,
                const Fractional &element,
                State &callerState,
                bool &stop
            ) = 0;
    };

	/*TESTS:
	 *
     *  (assert (= (+ "a") (error "first argument must be numeric")) "plus string")
	 *  (assert (= (+ 1 "a") (error "argument must be numeric")) "mixed plus")
	 */

#endif
