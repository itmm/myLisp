#if ! defined(fnnumeric_h)
#define fnnumeric_h

    #include "function.h"

    class FunctionNumeric : public Function {
        public:
			virtual EPtr apply_evaled(EPtr arguments, State &state) override;
    };

    /*TESTS:
     *
     *  (assert (= (numeric 7 3) "7.000"))
     *  (assert (= (numeric 1/2 3) "0.500"))
     *  (assert (= (numeric 1/7 5) "0.14286"))
     *  (assert (= (numeric 7/3 3) "2.333"))
     *  (assert (= (numeric 9999/10000 3) "1.000"))
     */
     
#endif
