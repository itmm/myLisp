#if !defined(fnerror_h)
#define fnerror_h

    #include "unary.h"

    class FunctionError : public UnaryFunction {
        protected:
            virtual EPtr apply_unary(EPtr arg, State &callerState) override;
    };

	/*TESTS:
	 *
	 *	(assert (= (error "test") (error "test")) "test error")
	 *
	 *	(assert (= (error 2) (error "error argument must be a string")) "error 2")
	 */

#endif
