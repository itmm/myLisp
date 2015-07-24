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
 *	(assert (number? infinity) "infinity")
 *	(assert (number? not-a-number) "not-a-number")
 *	(assert (function? +) "+")
 *	(assert (function? def) "def")
 *	(assert (number? true) "true")
 *	(assert (number? false) "false")
 *	(assert (function? list) "list")
 *	(assert (function? fn) "fn")
 *	(assert (function? eval) "eval")
 *	(assert (function? car) "car")
 *	(assert (function? cond) "cond")
 *	(assert (function? cdr) "cdr")
 *	(assert (function? =) "=")
 *	(assert (function? quote) "quote")
 *	(assert (function? import) "import")
 *	(assert (function? error) "error")
 *	(assert (function? *) "*")
 *	(assert (function? print) "print")
 *	(assert (function? err-print) "err-print")
 *	(assert (function? true?) "true?")
 *	(assert (function? false?) "false?")
 *	(assert (function? str-print) "str-print")
 *	(assert (function? pair?) "pair?")
 *	(assert (function? string?) "string?")
 *	(assert (function? number?) "number?")
 *	(assert (function? function?) "function?")
 *	(assert (function? error?) "error?")
 *	(assert (function? identifier?) "identifier?")
 *	(assert (function? dictionary?) "dictionary?")
 *	(assert (function? <) "<")
 *	(assert (function? and) "and")
 *	(assert (function? dict) "dict")
 *	(assert (function? expand) "expand")
 *	(assert (function? apply) "apply")
 *	(assert (function? /) "/")
 *	(assert (function? numerator) "numerator")
 *	(assert (function? denominator) "denominator")
 *	(assert (function? remainder) "remainder")
 */

#endif
