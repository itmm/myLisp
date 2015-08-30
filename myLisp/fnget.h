#if ! defined (fnget_h)
#define fnget_h

    #include "binary.h"

    class FunctionGet : public BinaryFunction {
		protected:
			virtual EPtr apply_binary(EPtr first, EPtr second, State &state) override;
    };

    /*TESTS:
     *
     *+ (def "d" (dict '("a" 2) (list "b" nil)))
     *
     *  (assert (= (get d "a") 2))
     *  (assert (= (get d "b") nil))
     *  (assert (= (get d "c") nil))
     */

    /*TESTS:
     *
     *  (assert (= (get 1 2) (error "first argument must be a dictionary")))
     *  (assert (= (get (dict) 2) (error "second argument must be a string")))
     */

#endif
