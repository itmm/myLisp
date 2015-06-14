#if !defined(fndefine_h)
#define fndefine_h

	#include "function.h"

	class FunctionDefine: public Function {
		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

#endif
