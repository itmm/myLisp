#if !defined(root_factory_h)
#define root_factory_h

	#include "creator.h"

	class RootFactory {
		public:
			RootFactory(Creator *creator): _creator(creator), _local_creator(false) {}
			RootFactory(): _creator(new Creator()), _local_creator(true) {}
			~RootFactory() { if (_local_creator) delete _creator; }

			Ptr root();

		private:
			RootFactory(const RootFactory &) = delete;
			RootFactory &operator=(const RootFactory &) = delete;

			Creator *_creator;
			bool _local_creator;
	};

/*TESTS:
 *
 *>	#include "dictionary.h"
 *> #include "number.h"
 *
 *> #define GET(key) RootFactory().root()->as_dictionary()->get(key)
 *> #define GET_NM(key) GET(key)->as_number()
 *> #define GET_FN(key) GET(key)->as_function()
 *
 *	GET_NM("Infinity")->value() == Fractional::infinity()
 *	GET_NM("NotANumber") != nullptr
 *	GET_FN("+") != nullptr
 *	GET_FN("def") != nullptr
 *	GET_NM("true") != nullptr
 *	GET_NM("false") != nullptr
 *	GET_FN("list") != nullptr
 *	GET_FN("fn") != nullptr
 *	GET_FN("eval") != nullptr
 *
 */

#endif
