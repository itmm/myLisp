#if !defined(fndynamic_h)
#define fndynamic_h

	#include "function.h"

	class FunctionDynamic: public Function {
		public:
			FunctionDynamic(Element *args, Element *body, bool macro, State &state): _args(args), _body(body), _macro(macro), _root(Element::as_dictionary(state.root())), _inserter(Element::as_dictionary(
				state.inserter()
			)) {}

			virtual void add_to_visit(Collector::Visitor &visitor) override;

			virtual Ptr apply(Ptr arguments, State &state) override;
		private:
			bool _macro;
			Element *_args;
			Element *_body;

			Dictionary *_root;
			Dictionary *_inserter;
	public:
		virtual void to_stream(std::ostream &stream, bool escape) const override;
	};


#endif
