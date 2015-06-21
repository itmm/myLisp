#if !defined(fnlambda_h)
#define fnlambda_h

	#include "function.h"

	class FunctionLambda: public Function {
	public:
		virtual Ptr apply(Ptr arguments, State &state) override;
	};

#endif
