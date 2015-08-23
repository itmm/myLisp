#if ! defined(fnrandom_h)
#define fnrandom_h

    #include "unary_numeric.h"

    class FunctionRandom : public UnaryNumericFunction {
        protected:
			virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
    };

    /*TESTS:
     *
     *  (assert (= (random 0) 0))
     *  (assert (< (random 5) 5))
     */
     
#endif
