#if !defined(fndo_h)
#define fndo_h

	#include "function.h"

	class FunctionDo: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};


#endif
