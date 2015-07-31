#if !defined(fnerror_h)
#define fnerror_h

    #include "function.h"

    class FunctionError : public Function {
        protected:
            virtual EPtr apply_evaled(EPtr args, State &callerState) override;
    };

	/*TESTS:
	 *
	 *	(assert (= (error "test") (error "test")) "test error")
	 *
	 *	(assert (= (error 2) (error 2)) "error ")
     *  (assert (= (error "sum must be" (+ 1 2)) (error "sum must be" 3)) "error with args")
	 */

#endif
