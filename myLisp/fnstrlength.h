#if ! defined(fnstrlength_h)
#define fnstrlength_h

    #include "unary.h"

    class FunctionStringLength : public UnaryFunction {
		protected:
			virtual EPtr apply_unary(EPtr arg, State &callerState) override;
    };

    /*TESTS:
     *
     *  (assert (= (_str-length "") 0))
     *  (assert (= (_str-length "abc i") 5))
     */

#endif
