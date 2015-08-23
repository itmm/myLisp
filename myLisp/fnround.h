#if ! defined(fnround_h)
#define fnround_h

    #include "unary_numeric.h"

    class FunctionRound : public UnaryNumericFunction {
        public:
			virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
    };

    /*TESTS:
     *
     *  (assert (= (round 1/2) 0))
     *  (assert (= (round 100/7) 14))
     *  (assert (= (round -7/5) -1))
     */

#endif
