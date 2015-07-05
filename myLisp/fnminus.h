#if !defined(fnminus_h)
#define fnminus_h

    #import "function.h"

    class FunctionMinus: public Function {
    public:
        virtual Ptr apply(Ptr arguments, State &state) override;
    };

	/*	Some strange behavior was added: (-) returns -1 and (- a) returns -a.
	 *	So - can be used as an unary operator and (+), (-) can be used to mark
	 *	different states as 0 and -1.
	 */

    /*TESTS:
     *
     *  (= (-) -1)
     *  (= (- 10 2 3) 5)
     *  (= (- -3) 3)
     *  (= (- 1/3 2) -5/3)
     */

#endif
