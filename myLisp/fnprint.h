#if ! defined(fnprint_h)
#define fnprint_h

	#include "function.h"

	class FunctionPrint: public Function {
		public:
			FunctionPrint(std::ostream &stream): _stream(stream) {}

			virtual Ptr apply(Ptr arguments, State &state) override;

		private:
			std::ostream &_stream;
	};


#endif