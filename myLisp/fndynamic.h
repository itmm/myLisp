#if !defined(fndynamic_h)
#define fndynamic_h

	#include "function.h"

	class FunctionDynamic: public Function {
		public:
			FunctionDynamic(Pair *args, Element *body): _args(args), _body(body) {}

			virtual Ptr apply(Ptr arguments, State &state) override;
		private:
			Pair *_args;
			Element *_body;
	};


#endif
