#if ! defined(fnround_h)
#define fnround_h

    #include "unary_numeric.h"

    class FunctionRound : public UnaryNumericFunction {
        public:
			virtual EPtr apply_unary_numeric(const Fractional &value, State &state) override;
    };

    /*TESTS:
     *
     *  (assert (= (round 1/2) 0) "round 1/2")
     *  (assert (= (round 100/7) 14) "round 100/7")
     *  (assert (= (round -7/5) -1) "round -7/5")
     */

#endif
