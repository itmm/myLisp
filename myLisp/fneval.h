#ifndef fneval_h
#define fneval_h

	#include "function.h"

	class FunctionEval: public  Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

#endif
