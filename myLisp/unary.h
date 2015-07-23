#if !defined(unary_h)
#define unary_h

	#include "function.h"

	class UnaryFunction : public Function {
		protected:
			virtual Ptr applyUnary(Ptr arg, State &callerState) = 0;

		public:
			virtual Ptr apply(Ptr arguments, State &state) override;
	};

#endif
