#if ! defined(fnprint_h)
#define fnprint_h

	#include "function.h"

	class FunctionPrint: public Function {
		public:
			FunctionPrint(std::ostream &stream): _stream(stream) {}

			virtual EPtr apply(EPtr arguments, State &state) override;

		private:
			std::ostream &_stream;
	};


#endif