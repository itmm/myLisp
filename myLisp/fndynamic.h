#if !defined(fndynamic_h)
#define fndynamic_h

	#include "function.h"

	class FunctionDynamic: public Function {
		public:
			FunctionDynamic(Pair *args, Element *body, bool macro): _args(args), _body(body), _macro(macro) {}

			virtual void add_to_visit(Collector::Visitor &visitor) override;

			virtual Ptr apply(Ptr arguments, State &state) override;
		private:
			bool _macro;
			Pair *_args;
			Element *_body;
	};


#endif
