#if !defined(fnminus_h)
#define fnminus_h

    #import "function.h"

    class FunctionMinus: public Function {
    public:
        virtual Ptr apply(Ptr arguments, State &state) override;
    };

    /*TESTS:
     *
     *>	#include "number.h"
     *
     *+ Parser p;
     *
     *	p.eval("(-)")->as_number()->value() == -Fractional(1)
     *	p.eval("(- 10 2 3)")->as_number()->value() == 5
     *  p.eval("(- -3)")->as_number()->value() == 3
     *
     */

#endif
